// ShootyBooty by @GazeePuk. All Rights Reversed

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "SBChangeWeaponBTService.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTYBOOTY_API USBChangeWeaponBTService : public UBTService
{
	GENERATED_BODY()

public:
	USBChangeWeaponBTService();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI", meta=(ClampMin = "0.0", ClampMax = "1.0"))
	float Probability = 0.5f;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
