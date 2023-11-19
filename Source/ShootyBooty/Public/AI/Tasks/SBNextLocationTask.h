// ShootyBooty by @GazeePuk. All Rights Reversed

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "SBNextLocationTask.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTYBOOTY_API USBNextLocationTask : public UBTTaskNode
{
	GENERATED_BODY()

public:
	USBNextLocationTask();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
	float Radius = 1000.0f;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="AI")
	FBlackboardKeySelector AimLocationKey;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="AI")
	bool bSelfCenter = true;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="AI", meta = (EditCondition = "!bSelfCenter"))
	FBlackboardKeySelector CenterActorKey;
};
