// ShootyBooty by @GazeePuk. All Rights Reversed

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AnnouncementWidget.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class SHOOTYBOOTY_API UAnnouncementWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetCountdownText(const FText& CountdownText) const;
	void SetCountdownText(float CountdownTime) const;
	void SetAnnouncementText(const FText& AnnouncementText) const;
protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> WarmupCountdownTextBlock;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> AnnouncementTextBlock;
	
};
