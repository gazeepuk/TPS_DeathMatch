// ShootyBooty by @GazeePuk. All Rights Reversed


#include "GameStates/DeathMatchGameState.h"

#include "SBPlayerController.h"
#include "Net/UnrealNetwork.h"
#include "PlayerStates/DeathMatchPlayerState.h"

ADeathMatchGameState::ADeathMatchGameState()
{
	bReplicates = true;
}

void ADeathMatchGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ADeathMatchGameState, TopScoringPlayerStates);
}

void ADeathMatchGameState::UpdateTopScore()
{
	if(!HasAuthority())
	{
		return;
	}
	
	TopScoringPlayerStates.Sort([](const ADeathMatchPlayerState& PlayerStateA, const ADeathMatchPlayerState& PlayerStateB)
	{
		return PlayerStateA.GetScore() > PlayerStateB.GetScore();
	});

	for(FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		ASBPlayerController* SBPlayerController = Cast<ASBPlayerController>(*It);
		SBPlayerController->OnTopScoringPlayersSet(TopScoringPlayerStates);
	}
}

void ADeathMatchGameState::AddPlayerState(APlayerState* PlayerState)
{
	Super::AddPlayerState(PlayerState);
	
	if(ADeathMatchPlayerState* DeathMatchPlayerState = Cast<ADeathMatchPlayerState>(PlayerState))
	{
		TopScoringPlayerStates.AddUnique(DeathMatchPlayerState);
	}
	UpdateTopScore();
}

void ADeathMatchGameState::RemovePlayerState(APlayerState* PlayerState)
{
	if(ADeathMatchPlayerState* DeathMatchPlayerState = Cast<ADeathMatchPlayerState>(PlayerState))
	{
		TopScoringPlayerStates.Remove(DeathMatchPlayerState);
	}
	Super::RemovePlayerState(PlayerState);
	
	UpdateTopScore();
}
