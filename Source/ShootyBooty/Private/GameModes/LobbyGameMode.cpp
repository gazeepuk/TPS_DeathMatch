// Developed by Ivan Piankouski
// GitHub / LinkedIn: gazeepuk


#include "GameModes/LobbyGameMode.h"

#include "GameFramework/GameSession.h"

void ALobbyGameMode::KickPlayer(APlayerController* InPlayerControllerToKick, const FText& KickReason)
{
	if(GameSession && InPlayerControllerToKick)
	{
		GameSession->KickPlayer(InPlayerControllerToKick, KickReason);
	}
}
