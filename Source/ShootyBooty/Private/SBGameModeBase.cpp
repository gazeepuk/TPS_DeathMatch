// ShootyBooty by @GazeePuk. All Rights Reversed


#include "SBGameModeBase.h"

#include "SBBaseCharacter.h"
#include "SBGameHUD.h"
#include"Player/SBPlayerController.h"
ASBGameModeBase::ASBGameModeBase()
{
	DefaultPawnClass = ASBBaseCharacter::StaticClass();
	PlayerControllerClass = ASBPlayerController::StaticClass();
	HUDClass = ASBGameHUD::StaticClass();
}
