// ShootyBooty by @GazeePuk. All Rights Reversed


#include "UI/SBGameHUD.h"

#include "SBPlayerController.h"
#include "SBPlayerHUDWidget.h"
#include "Blueprint/UserWidget.h"

void ASBGameHUD::AddHUDWidget()
{
	ASBPlayerController* SBPlayerController = GetOwningPlayerController() ? Cast<ASBPlayerController>(GetOwningPlayerController()) : nullptr;
	if(SBPlayerController && PlayerHUDWidgetClass)
	{
		PlayerHUDWidget = CreateWidget<USBPlayerHUDWidget>(SBPlayerController, PlayerHUDWidgetClass);
		if(PlayerHUDWidget)
		{
			PlayerHUDWidget->AddToViewport();
		}
	}
}

void ASBGameHUD::BeginPlay()
{
	Super::BeginPlay();

}
