// ShootyBooty by @GazeePuk. All Rights Reversed


#include "SBGameModeBase.h"

#include "SBBaseCharacter.h"
#include "SBGameHUD.h"
#include "Controllers/DeathMatchPlayerController.h"
ASBGameModeBase::ASBGameModeBase()
{
	DefaultPawnClass = ASBBaseCharacter::StaticClass();
	PlayerControllerClass = ADeathMatchPlayerController::StaticClass();
	HUDClass = ASBGameHUD::StaticClass();
}
