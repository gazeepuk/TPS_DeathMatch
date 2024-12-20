// Developed by Ivan Piankouski
// GitHub / LinkedIn: gazeepuk

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
