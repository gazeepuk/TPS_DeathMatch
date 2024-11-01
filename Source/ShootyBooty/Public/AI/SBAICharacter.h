// ShootyBooty by @GazeePuk. All Rights Reversed

#pragma once

#include "CoreMinimal.h"
#include "SBBaseCharacter.h"
#include "SBAICharacter.generated.h"

class UBehaviorTree;

UCLASS()
class SHOOTYBOOTY_API ASBAICharacter : public ASBBaseCharacter
{
	GENERATED_BODY()
public:
	ASBAICharacter(const FObjectInitializer& ObjInit);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="AI")
	UBehaviorTree* BehaviorTreeAsset;

protected:
	virtual void OnDeath() override;
};
