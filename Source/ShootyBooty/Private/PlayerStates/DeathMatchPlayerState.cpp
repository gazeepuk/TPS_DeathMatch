// ShootyBooty by @GazeePuk. All Rights Reversed


#include "PlayerStates/DeathMatchPlayerState.h"

#include "SBPlayerController.h"
#include "GameStates/DeathMatchGameState.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

ADeathMatchPlayerState::ADeathMatchPlayerState()
{
	bReplicates = true;
	NetUpdateFrequency = 45.f;
}

void ADeathMatchPlayerState::AddScore(const float AdditiveValue)
{
	SetScore(GetScore() + AdditiveValue);
	OnScoreSet();
	
}

void ADeathMatchPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ADeathMatchPlayerState, Defeats);
}

void ADeathMatchPlayerState::OnRep_Score()
{
	Super::OnRep_Score();
	OnScoreSet();
}

void ADeathMatchPlayerState::OnScoreSet()
{
	if(!SBPlayerController)
	{
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		SBPlayerController = PlayerController ? Cast<ASBPlayerController>(PlayerController) : nullptr;
	}

	if(!SBPlayerController)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerController is nullptr for %s"), *GetNameSafe(this))
		return;
	}

	DeathMatchGameState = DeathMatchGameState == nullptr ? GetWorld()->GetGameState<ADeathMatchGameState>() : DeathMatchGameState;
	if(!DeathMatchGameState)
	{
		UE_LOG(LogTemp, Error, TEXT("GameState is nullptr for %s"), *GetNameSafe(this));
		return;
	}

	TArray<APlayerState*> TopScoringPlayers = DeathMatchGameState->GetTopScoringPlayers();
	SBPlayerController->SetTopScoringPlayer(TopScoringPlayers);
}

