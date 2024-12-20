// Developed by Ivan Piankouski
// GitHub / LinkedIn: gazeepuk

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "SBFireService.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTYBOOTY_API USBFireService : public UBTService
{
	GENERATED_BODY()
	
public:
	USBFireService();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector EnemyActorKey;

	//Firing weapon
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
