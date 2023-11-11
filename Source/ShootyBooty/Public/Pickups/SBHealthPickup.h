// ShootyBooty by @GazeePuk. All Rights Reversed

#pragma once

#include "CoreMinimal.h"
#include "Pickups/SBBasePickup.h"
#include "SBHealthPickup.generated.h"

UCLASS()
class SHOOTYBOOTY_API ASBHealthPickup : public ASBBasePickup
{
	GENERATED_BODY()

protected:
	virtual bool GivePickupTo(APawn* InPlayerPawn) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup", meta = (ClampMin = "0", ClampMax = "100"))
	float HealAmount = 15;
};
