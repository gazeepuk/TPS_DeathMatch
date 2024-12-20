// Developed by Ivan Piankouski
// GitHub / LinkedIn: gazeepuk


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
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	if (Blackboard)
	{
		const AAIController* Controller = OwnerComp.GetAIOwner();
		const USBAIPerceptionComponent* PerceptionComponent = Controller->FindComponentByClass<USBAIPerceptionComponent>();
		if(PerceptionComponent)
		{
			Blackboard->SetValueAsObject(EnemyActorKey.SelectedKeyName, PerceptionComponent->GetClosestEnemy());
		}
	}
	Super::TickNode(OwnerComp,NodeMemory,DeltaSeconds);
}
