// ShootyBooty by @GazeePuk. All Rights Reversed


#include "PlayerStates/DeathMatchPlayerState.h"

#include "GameStates/DeathMatchGameState.h"

void ADeathMatchPlayerState::AddScore()
{
	SetScore(GetScore() + 1.f);
	//Updates Top Score in GameState
	if(ADeathMatchGameState* DeathMatchGameState = GetWorld()->GetGameState<ADeathMatchGameState>())
	{
		DeathMatchGameState->UpdateTopScore();
	}
}
