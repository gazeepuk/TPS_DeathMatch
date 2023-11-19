// ShootyBooty by @GazeePuk. All Rights Reversed

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SBAIController.generated.h"

class USBAIPerceptionComponent;
/**
 * 
 */
UCLASS()
class SHOOTYBOOTY_API ASBAIController : public AAIController
{
	GENERATED_BODY()

public:
	ASBAIController();
protected:
UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USBAIPerceptionComponent* SBAIPerceptionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FName FocusOnKeyName = "EnemyActor";
	
	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaSeconds) override;

private:
	AActor* GetFocusOnActor();
};
