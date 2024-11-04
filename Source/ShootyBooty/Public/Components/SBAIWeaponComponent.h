// ShootyBooty by @GazeePuk. All Rights Reversed

#pragma once

#include "CoreMinimal.h"
#include "SBWeaponComponent.h"
#include "SBAIWeaponComponent.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTYBOOTY_API USBAIWeaponComponent : public USBWeaponComponent
{
	GENERATED_BODY()

public:
	virtual void StartFire() override;
	virtual void EquipNextWeapon() override;
};
 