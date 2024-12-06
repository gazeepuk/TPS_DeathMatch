// ShootyBooty by @GazeePuk. All Rights Reversed


#include "SBPlayerController.h"

#include "AnnouncementWidget.h"
#include "EnhancedInputSubsystems.h"
#include "SBGameHUD.h"
#include "SBPlayerHUDWidget.h"
#include "Components/TextBlock.h"
#include "GameFramework/GameMode.h"
#include "GameFramework/GameState.h"
#include "GameModes/DeathMatchGameMode.h"
#include "GameStates/DeathMatchGameState.h"
#include "Net/UnrealNetwork.h"

ASBPlayerController::ASBPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASBPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem)
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	SBGameHUD = GetHUD<ASBGameHUD>();
	Server_CheckMatchState();
}

void ASBPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASBPlayerController, MatchState);
}

void ASBPlayerController::Server_CheckMatchState_Implementation()
{
	const ADeathMatchGameMode* DeathMatchGameMode = GetWorld()->GetAuthGameMode<ADeathMatchGameMode>();
	if(DeathMatchGameMode)
	{
		WarmupTime = DeathMatchGameMode->GetWarmupTime();
		MatchTime = DeathMatchGameMode->GetMatchTime();
		CooldownTime = DeathMatchGameMode->GetCooldownTime();
		LevelStartingTime = DeathMatchGameMode->GetLevelStartingTime();
		MatchState = DeathMatchGameMode->GetMatchState();
		Client_JoinMidgame(MatchState, WarmupTime, CooldownTime, MatchTime, LevelStartingTime);

		if(SBGameHUD && MatchState == MatchState::WaitingToStart && IsLocalController())
		{
			SBGameHUD->AddAnnouncementWidget();
		}
	}
}

void ASBPlayerController::Client_JoinMidgame_Implementation(FName InMatchState, float InWarmupTime, float InCooldownTime,
                                                            float InMatchTime, float InLevelStartingTime)
{
	MatchState = InMatchState;
	WarmupTime = InWarmupTime;
	MatchTime = InMatchTime;
	CooldownTime = InCooldownTime;
	LevelStartingTime = InLevelStartingTime;
	OnMatchStateSet(MatchState);
	
	if(SBGameHUD && MatchState == MatchState::WaitingToStart)
	{
		SBGameHUD->AddAnnouncementWidget();
	}
}

void ASBPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	SetHUDTime();
	CheckTimeSynced(DeltaSeconds);
}

void ASBPlayerController::CheckTimeSynced(float DeltaSeconds)
{
	TimeSyncRunningTime +=  DeltaSeconds;

	if(IsLocalController() && TimeSyncRunningTime > TimeSyncFrequency)
	{
		Server_RequestServerTime(GetWorld()->GetTimeSeconds());
		TimeSyncRunningTime = 0.f;
	}
}


void ASBPlayerController::SetHUDTime()
{

	float TimeLeft = 0.f;
	if(MatchState == MatchState::WaitingToStart)
	{
		TimeLeft = WarmupTime - GetServerTime() + LevelStartingTime;
	}
	else if (MatchState == MatchState::InProgress)
	{
		TimeLeft = WarmupTime + MatchTime - GetServerTime() + LevelStartingTime;
	}
	else if(MatchState == MatchState::Cooldown)
	{
		TimeLeft = CooldownTime + WarmupTime + MatchTime - GetServerTime() + LevelStartingTime;
	}
	
	uint32 SecondLeft = FMath::CeilToInt(TimeLeft);

	if(CountdownInt != SecondLeft)
	{
		if(MatchState == MatchState::WaitingToStart || MatchState == MatchState::Cooldown)
		{
			SetAnnouncementCountdown(TimeLeft);
		}
		else if(MatchState == MatchState::InProgress)
		{
			SetHUDMatchCountdown(TimeLeft);
		}
	}
	CountdownInt = SecondLeft;
}

void ASBPlayerController::Server_RequestServerTime_Implementation(float TimeOfClientRequest)
{
	float ServerTimeOfReceipt = GetWorld()->GetTimeSeconds();

	Client_ReportServerTime(TimeOfClientRequest, ServerTimeOfReceipt);
}

void ASBPlayerController::Client_ReportServerTime_Implementation(float TimeOfClientRequest,
	float TimeServerReceivedClientRequest)
{
	float RoundTripTime = GetWorld()->GetTimeSeconds() - TimeOfClientRequest;
	float ServerCurrentTime = TimeServerReceivedClientRequest + RoundTripTime / 2;

	ClientServerDelta = ServerCurrentTime - GetWorld()->GetTimeSeconds();
}


void ASBPlayerController::SetHUDMatchCountdown(const float CountdownTime)
{
	SBGameHUD = SBGameHUD == nullptr ? GetHUD<ASBGameHUD>() : SBGameHUD;
	const bool bHUDValid = SBGameHUD && SBGameHUD->PlayerHUDWidget;
	if(bHUDValid)
	{
		SBGameHUD->PlayerHUDWidget->SetCountdownText(CountdownTime);
	}
}

void ASBPlayerController::SetAnnouncementCountdown(float CountdownTime)
{
	SBGameHUD = SBGameHUD == nullptr ? GetHUD<ASBGameHUD>() : SBGameHUD;
	const bool bHUDValid = SBGameHUD && SBGameHUD->AnnouncementWidget;
	if(bHUDValid)
	{
		SBGameHUD->AnnouncementWidget->SetCountdownText(CountdownTime);
	}
}

void ASBPlayerController::SetTopScoringPlayer(const TArray<APlayerState*>& InTopScoringPlayerStates)
{
	SBGameHUD = SBGameHUD == nullptr ? GetHUD<ASBGameHUD>() : SBGameHUD;
	const bool bHUDValid = SBGameHUD && SBGameHUD->PlayerHUDWidget;
	if(bHUDValid)
	{
		SBGameHUD->PlayerHUDWidget->OnTopScoringPlayersSet(InTopScoringPlayerStates);
	}
}



float ASBPlayerController::GetServerTime()
{
	if(HasAuthority())
	{
		return GetWorld()->GetTimeSeconds();
	}
	
	return GetWorld()->GetTimeSeconds() + ClientServerDelta;
}

void ASBPlayerController::ReceivedPlayer()
{
	Super::ReceivedPlayer();
	if(IsLocalController())
	{
		Server_RequestServerTime(GetWorld()->GetTimeSeconds());
	}
}

void ASBPlayerController::OnRep_MatchState()
{
	// Adding HUD to viewport and hiding Announcement widget on client
	if(MatchState == MatchState::InProgress)
	{
		HandleMatchHasStarted();
	}
	else if(MatchState == MatchState::Cooldown)
	{
		HandleCooldown();
	}
}

void ASBPlayerController::OnMatchStateSet(FName InMatchState)
{
	MatchState = InMatchState;

	// Adding HUD to viewport and hiding Announcement widget on listen-server
	if(MatchState == MatchState::InProgress && IsLocalController())
	{
		HandleMatchHasStarted();
	}
	else if(MatchState == MatchState::Cooldown)
	{
		HandleCooldown();
	}
}

void ASBPlayerController::HandleMatchHasStarted()
{
	SBGameHUD = SBGameHUD == nullptr ? GetHUD<ASBGameHUD>() : SBGameHUD;
	if(SBGameHUD)
	{
		SBGameHUD->AddHUDWidget();
		AGameState* GameState = GetWorld()->GetGameState<AGameState>();
		if(SBGameHUD->PlayerHUDWidget && GameState)
		{
			SBGameHUD->PlayerHUDWidget->OnTopScoringPlayersSet(GameState->PlayerArray);
		}
		if(SBGameHUD->AnnouncementWidget)
		{
			SBGameHUD->AnnouncementWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void ASBPlayerController::HandleCooldown()
{
	SBGameHUD = SBGameHUD == nullptr ? GetHUD<ASBGameHUD>() : SBGameHUD;
	if(SBGameHUD)
	{
		if(SBGameHUD->PlayerHUDWidget)
		{
			SBGameHUD->PlayerHUDWidget->RemoveFromParent();
		}
		if(SBGameHUD->AnnouncementWidget)
		{
			SBGameHUD->AnnouncementWidget->SetVisibility(ESlateVisibility::Visible);
			FString AnnouncementText("New Match starts in:");
			SBGameHUD->AnnouncementWidget->SetAnnouncementText(FText::FromString(AnnouncementText));

			ADeathMatchGameState* DeathMatchGameState = GetWorld()->GetGameState<ADeathMatchGameState>();
			if(DeathMatchGameState)
			{
				SBGameHUD->AnnouncementWidget->SetTopScoringPlayers(DeathMatchGameState->GetTopScoringPlayers());
			}
		}
	}
}
