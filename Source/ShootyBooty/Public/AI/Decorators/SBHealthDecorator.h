// ShootyBooty by @GazeePuk. All Rights Reversed

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "SBHealthDecorator.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTYBOOTY_API USBHealthDecorator : public UBTDecorator
{
	GENERATED_BODY()
public:
	USBHealthDecorator();
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
	float HealthPercent = 0.6f;
	
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
