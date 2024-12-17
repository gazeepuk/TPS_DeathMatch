// ShootyBooty by @GazeePuk. All Rights Reversed


#include "UI/SBGameHUD.h"

#include "AnnouncementWidget.h"
#include "Controllers/DeathMatchPlayerController.h"
#include "SBPlayerHUDWidget.h"
#include "Blueprint/UserWidget.h"

void ASBGameHUD::AddHUDWidget()
{
	if(PlayerHUDWidget)
	{
		return;
	}
	
	ADeathMatchPlayerController* SBPlayerController = GetOwningPlayerController() ? Cast<ADeathMatchPlayerController>(GetOwningPlayerController()) : nullptr;
	if(SBPlayerController && PlayerHUDWidgetClass)
	{
		PlayerHUDWidget = CreateWidget<USBPlayerHUDWidget>(SBPlayerController, PlayerHUDWidgetClass);
		if(PlayerHUDWidget)
		{
			PlayerHUDWidget->AddToViewport();
		}
	}
}

void ASBGameHUD::AddAnnouncementWidget()
{
	if(AnnouncementWidget)
	{
		return;
	}
	
	ADeathMatchPlayerController* SBPlayerController = GetOwningPlayerController() ? Cast<ADeathMatchPlayerController>(GetOwningPlayerController()) : nullptr;
	if(SBPlayerController && AnnouncementWidgetClass)
	{
		AnnouncementWidget = CreateWidget<UAnnouncementWidget>(SBPlayerController, AnnouncementWidgetClass);
		if(AnnouncementWidgetClass)
		{
			AnnouncementWidget->AddToViewport();
		}
	}
}

void ASBGameHUD::BeginPlay()
{
	Super::BeginPlay();

}
