// Developed by Ivan Piankouski
// GitHub / LinkedIn: gazeepuk

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include"SBBaseWeapon.h"
#include "SBPlayerHUDWidget.generated.h"

/**
 * 
 */

class UTextBlock;
class USBWeaponComponent;
class USBHealthComponent;

UCLASS()
class SHOOTYBOOTY_API USBPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="UI")
	float GetHealthPercent() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="UI")
	bool GetWeaponUIData(FWeaponUIData& UIData);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="UI")
	bool GetWeaponAmmoData(FAmmoData& Ammo);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="UI")
	bool IsPlayerAlive() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="UI")
	bool IsPlayerSpectating() const;

	void SetCountdownText(float CountdownTime) const;
	void SetCountdownText(const FText& CountdownText) const;

	UFUNCTION(BlueprintImplementableEvent)
	void OnTopScoringPlayersSet(const TArray<APlayerState*>& InTopScoringPlayers);
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> MatchCountdownTextBlock;
};