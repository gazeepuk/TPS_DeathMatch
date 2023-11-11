// ShootyBooty by @GazeePuk. All Rights Reversed

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include"SBBaseWeapon.h"
#include "SBPlayerHUDWidget.generated.h"

/**
 * 
 */

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

};