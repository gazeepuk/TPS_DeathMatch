// Developed by Ivan Piankouski
// GitHub / LinkedIn: gazeepuk

#pragma once

#include "CoreMinimal.h"
#include "SBHealthComponent.h"
#include "SBWeaponComponent.h"
#include "SBUtils.generated.h"

UCLASS()
class SHOOTYBOOTY_API USBUtils : public UObject
{
	GENERATED_BODY()
	
public:
	static USBWeaponComponent* GetWeaponComponent(const APawn* InPlayerPawn);
	static USBHealthComponent* GetHealthComponent(const AActor* InPlayerPawn);
};
