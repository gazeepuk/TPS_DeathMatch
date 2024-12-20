// Developed by Ivan Piankouski
// GitHub / LinkedIn: gazeepuk


#include "PlayerStates/LobbyPlayerState.h"

#include "Controllers/LobbyPlayerController.h"

void ALobbyPlayerState::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* FirstPlayerController =  GetWorld()->GetFirstPlayerController();
	ALobbyPlayerController* LobbyPlayerController = FirstPlayerController ? Cast<ALobbyPlayerController>(FirstPlayerController) : nullptr;
	if(LobbyPlayerController)
	{
		LobbyPlayerController->UpdatePlayerList();
	}
}
