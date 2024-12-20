// Developed by Ivan Piankouski
// GitHub / LinkedIn: gazeepuk


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
