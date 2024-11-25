// ShootyBooty by @GazeePuk. All Rights Reversed


#include "SBPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "SBGameHUD.h"
#include "SBPlayerHUDWidget.h"
#include "Components/TextBlock.h"
#include "GameFramework/GameMode.h"
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
}

void ASBPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASBPlayerController, MatchState); 
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
	uint32 SecondLeft = FMath::CeilToInt(MatchTime - GetServerTime());

	if(CountdownInt != SecondLeft)
	{
		SetHUDMatchCountdown(MatchTime - GetServerTime());
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


void ASBPlayerController::SetHUDMatchCountdown(float CountdownTime)
{
	SBGameHUD = SBGameHUD == nullptr ? GetHUD<ASBGameHUD>() : SBGameHUD;
	const bool bHUDValid = SBGameHUD && SBGameHUD->PlayerHUDWidget && SBGameHUD->PlayerHUDWidget->MatchCountdownTextBlock;
	if(bHUDValid)
	{
		int32 Minutes = FMath::FloorToInt(CountdownTime / 60.f);
		int32 Seconds = CountdownTime - Minutes * 60;
		FString CountdownText = FString::Printf(TEXT("%02d:%02d"), Minutes, Seconds);
		SBGameHUD->PlayerHUDWidget->MatchCountdownTextBlock->SetText(FText::FromString(CountdownText));
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
	if(MatchState == MatchState::InProgress)
	{
		SBGameHUD = SBGameHUD == nullptr ? GetHUD<ASBGameHUD>() : SBGameHUD;
		if(SBGameHUD)
		{
			SBGameHUD->AddHUDWidget();
		}
	}
}

void ASBPlayerController::OnMatchStateSet(FName InMatchState)
{
	MatchState = InMatchState;

	// Adding HUD widget to viewport
	if(MatchState == MatchState::InProgress)
	{
		SBGameHUD = SBGameHUD == nullptr ? GetHUD<ASBGameHUD>() : SBGameHUD;
		if(SBGameHUD)
		{
			SBGameHUD->AddHUDWidget();
		}
	}
}
