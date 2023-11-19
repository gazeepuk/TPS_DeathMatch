// ShootyBooty by @GazeePuk. All Rights Reversed


#include "AI/Services/SBFindEnemyBTService.h"

#include "AIController.h"
#include "SBAIPerceptionComponent.h"
#include "SBUtils.h"
#include "BehaviorTree/BlackboardComponent.h"

USBFindEnemyBTService::USBFindEnemyBTService()
{
	NodeName = "FindEnemy";
}

void USBFindEnemyBTService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	if (Blackboard)
	{
		const auto Controller = OwnerComp.GetAIOwner();
		const auto PerceptionComponent = Controller->FindComponentByClass<USBAIPerceptionComponent>();
		if(PerceptionComponent)
		{
			Blackboard->SetValueAsObject(EnemyActorKey.SelectedKeyName, PerceptionComponent->GetClosestEnemy());
		}
	}
	Super::TickNode(OwnerComp,NodeMemory,DeltaSeconds);
}
