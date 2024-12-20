// Developed by Ivan Piankouski. GitHub / LinkedIn: gazeepuk

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

	// Checking if AI-character should find a Health pickup 
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
