// ShootyBooty by @GazeePuk. All Rights Reversed


#include "AI/Services/SBFireService.h"

#include "AIController.h"
#include "SBWeaponComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

USBFireService::USBFireService()
{
	NodeName = "Fire";
}

void USBFireService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Controller = OwnerComp.GetAIOwner();
	const auto Blackboard = OwnerComp.GetBlackboardComponent();

	const bool bHasName = Blackboard && Blackboard->GetValueAsObject(EnemyActorKey.SelectedKeyName);

	if(Controller)
	{
		const auto WeaponComponent = Controller->GetPawn()->FindComponentByClass<USBWeaponComponent>();
		if(WeaponComponent)
		{
			bHasName ? WeaponComponent->StartFire() : WeaponComponent->StopFire();
		}
	}
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	
}
