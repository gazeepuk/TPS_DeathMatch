// ShootyBooty by @GazeePuk. All Rights Reversed

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "SBFindEnemyBTService.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTYBOOTY_API USBFindEnemyBTService : public UBTService
{
	GENERATED_BODY()

public:
	USBFindEnemyBTService();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
	FBlackboardKeySelector EnemyActorKey;
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
