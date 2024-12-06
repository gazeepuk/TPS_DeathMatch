// ShootyBooty by @GazeePuk. All Rights Reversed


#include "GameStates/DeathMatchGameState.h"

#include "Net/UnrealNetwork.h"
#include "PlayerStates/DeathMatchPlayerState.h"

ADeathMatchGameState::ADeathMatchGameState()
{
	bReplicates = true;
}

TArray<APlayerState*> ADeathMatchGameState::GetTopScoringPlayers() const
{
	TArray<APlayerState*> TopScoringPlayers;
	TopScoringPlayers.Append(PlayerArray);
	TopScoringPlayers.Sort([](const APlayerState& PlayerStateA, const APlayerState& PlayerStateB)
	{
		return PlayerStateA.GetScore() > PlayerStateB.GetScore();
	});

	return TopScoringPlayers;
}
