// ShootyBooty by @GazeePuk. All Rights Reversed


#include "GameModes/DeathMatchGameMode.h"

#include "SBPlayerCharacter.h"
#include "Controllers/DeathMatchPlayerController.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerStates/DeathMatchPlayerState.h"

namespace MatchState
{
	const FName Cooldown = FName("Cooldown");
}


ADeathMatchGameMode::ADeathMatchGameMode()
{
	PrimaryActorTick.bCanEverTick = true;

	bDelayedStart = true;
}

void ADeathMatchGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(MatchState == MatchState::WaitingToStart)
	{
		CountdownTime = WarmupTime - GetWorld()->GetTimeSeconds() + LevelStartingTime;
		if(CountdownTime <= 0.f)
		{
			StartMatch();
		}
	}
	else if(MatchState == MatchState::InProgress)
	{
		CountdownTime = MatchTime + WarmupTime - GetWorld()->GetTimeSeconds() + LevelStartingTime;
		if(CountdownTime <= 0.f)
		{
			SetMatchState(MatchState::Cooldown);
		}
	}
	else if(MatchState == MatchState::Cooldown)
	{
		CountdownTime = CooldownTime + MatchTime + WarmupTime - GetWorld()->GetTimeSeconds() + LevelStartingTime;
		if(CountdownTime <= 0.f)
		{
			RestartGame();
		}
	}
}

void ADeathMatchGameMode::PlayerEliminated(ASBPlayerCharacter* EliminatedCharacter,
	ADeathMatchPlayerController* VictimController, ADeathMatchPlayerController* AttackerController)
{
	if(EliminatedCharacter)
	{
		EliminatedCharacter->OnDeath();
	}

	if(AttackerController)
	{
		ADeathMatchPlayerState* DeathMatchPlayerState = AttackerController->GetPlayerState<ADeathMatchPlayerState>();
		if(DeathMatchPlayerState)
		{
			DeathMatchPlayerState->AddScore(1);
		}
	}
	if(VictimController)
	{
		ADeathMatchPlayerState* DeathMatchPlayerState = VictimController->GetPlayerState<ADeathMatchPlayerState>();
		if(DeathMatchPlayerState)
		{
			DeathMatchPlayerState->AddDefeats(1);
		}
	}
}

void ADeathMatchGameMode::RespawnPlayer(ACharacter* EliminatedCharacter, AController* EliminatedController)
{
	if(EliminatedCharacter)
	{
		EliminatedCharacter->Reset();
		EliminatedCharacter->Destroy();
	}
	if(EliminatedController)
	{
		TArray<AActor*> AllPlayerStarts;
		UGameplayStatics::GetAllActorsOfClass(this, APlayerStart::StaticClass(), AllPlayerStarts);
		int32 RandomPlayerStartIndex = FMath::RandRange(0, AllPlayerStarts.Num() - 1);
		RestartPlayerAtPlayerStart(EliminatedController, AllPlayerStarts[RandomPlayerStartIndex]);
	}
}

void ADeathMatchGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	AllPlayerControllers.AddUnique(NewPlayer);
}

void ADeathMatchGameMode::SwapPlayerControllers(APlayerController* OldPC, APlayerController* NewPC)
{
	Super::SwapPlayerControllers(OldPC, NewPC);
	AllPlayerControllers.AddUnique(NewPC);
}

void ADeathMatchGameMode::Logout(AController* Exiting)
{
	if(APlayerController* PlayerController = Cast<APlayerController>(Exiting))
	{
		AllPlayerControllers.Remove(PlayerController);
	}
	Super::Logout(Exiting);
}

void ADeathMatchGameMode::BeginPlay()
{
	Super::BeginPlay();

	LevelStartingTime = GetWorld()->GetTimeSeconds();
}

void ADeathMatchGameMode::OnMatchStateSet()
{
	Super::OnMatchStateSet();

	for(FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		ADeathMatchPlayerController* PlayerController = Cast<ADeathMatchPlayerController>(*It);
		if(PlayerController)
		{
			PlayerController->OnMatchStateSet(MatchState);
		}
	}
}


