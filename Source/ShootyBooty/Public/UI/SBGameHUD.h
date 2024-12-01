// ShootyBooty by @GazeePuk. All Rights Reversed

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SBGameHUD.generated.h"

class UAnnouncementWidget;
class USBPlayerHUDWidget;
/**
 * 
 */
UCLASS()
class SHOOTYBOOTY_API ASBGameHUD : public AHUD
{
	GENERATED_BODY()
public:
	TObjectPtr<USBPlayerHUDWidget> PlayerHUDWidget;
	TObjectPtr<UAnnouncementWidget> AnnouncementWidget;

	void AddHUDWidget();
	void AddAnnouncementWidget();
protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> PlayerHUDWidgetClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> AnnouncementWidgetClass;
};
