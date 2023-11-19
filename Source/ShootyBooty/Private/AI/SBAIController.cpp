// ShootyBooty by @GazeePuk. All Rights Reversed


#include "AI/SBAIController.h"

#include "SBAIPerceptionComponent.h"
#include "AI/SBAICharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

ASBAIController::ASBAIController()
{
	SBAIPerceptionComponent = CreateDefaultSubobject<USBAIPerceptionComponent>("AIPerceptionComponent");
	SetPerceptionComponent(*SBAIPerceptionComponent);
}

void ASBAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	const ASBAICharacter* SBCharacter = Cast<ASBAICharacter>(InPawn);
	if(!SBCharacter)
	{
		return;
	}
	RunBehaviorTree(SBCharacter->BehaviorTreeAsset);
}

void ASBAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	const auto AimActor = GetFocusOnActor();
	SetFocus(AimActor);
}

AActor* ASBAIController::GetFocusOnActor()
{
	if(!GetBlackboardComponent())
	{
		return nullptr;
	}
	return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(FocusOnKeyName));
}
