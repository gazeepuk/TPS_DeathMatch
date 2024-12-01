// ShootyBooty by @GazeePuk. All Rights Reversed


#include "GameModes/DeathMatchGameMode.h"
#include "SBPlayerController.h"

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
		ASBPlayerController* PlayerController = Cast<ASBPlayerController>(*It);
		if(PlayerController)
		{
			PlayerController->OnMatchStateSet(MatchState);
		}
	}
}


