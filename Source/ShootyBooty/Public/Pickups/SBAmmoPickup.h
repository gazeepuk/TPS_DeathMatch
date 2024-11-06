// ShootyBooty by @GazeePuk. All Rights Reversed

#pragma once

#include "CoreMinimal.h"
#include "Pickups/SBBasePickup.h"
#include "SBAmmoPickup.generated.h"

class ASBBaseWeapon;
/**
 * 
 */
UCLASS()
class SHOOTYBOOTY_API ASBAmmoPickup : public ASBBasePickup
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Pickup", meta = (ClampMin="0", ClampMax="10"))
	int32  ClipsAmount = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Pickup")
	TSubclassOf<ASBBaseWeapon> WeaponType;
	virtual bool GivePickupTo(APawn* InPlayerPawn)  override;
};
