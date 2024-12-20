// Developed by Ivan Piankouski
// GitHub / LinkedIn: gazeepuk

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
	
	UFUNCTION(BlueprintImplementableEvent)
	void SetTopScoringPlayers(const TArray<APlayerState*>& TopScoringPlayers);
protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> WarmupCountdownTextBlock;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> AnnouncementTextBlock;
	
};
