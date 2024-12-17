// ShootyBooty by @GazeePuk. All Rights Reversed


#include "GameModes/LobbyGameMode.h"

#include "GameFramework/GameSession.h"

void ALobbyGameMode::KickPlayer(APlayerController* InPlayerControllerToKick, const FText& KickReason)
{
	if(GameSession && InPlayerControllerToKick)
	{
		GameSession->KickPlayer(InPlayerControllerToKick, KickReason);
	}
}
