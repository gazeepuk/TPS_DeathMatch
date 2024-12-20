// Developed by Ivan Piankouski
// GitHub / LinkedIn: gazeepuk


#include "GameStates/LobbyGameState.h"

#include "Controllers/LobbyPlayerController.h"

void ALobbyGameState::RemovePlayerState(APlayerState* PlayerState)
{
	Super::RemovePlayerState(PlayerState);

	APlayerController* FirstPlayerController =  GetWorld()->GetFirstPlayerController();
	ALobbyPlayerController* LobbyPlayerController = FirstPlayerController ? Cast<ALobbyPlayerController>(FirstPlayerController) : nullptr;
	if(LobbyPlayerController)
	{
		LobbyPlayerController->UpdatePlayerList();
	}
}
