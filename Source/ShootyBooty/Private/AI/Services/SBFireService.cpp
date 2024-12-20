// Developed by Ivan Piankouski
// GitHub / LinkedIn: gazeepuk


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
	const AAIController* Controller = OwnerComp.GetAIOwner();
	const UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();

	const bool bHasName = Blackboard && Blackboard->GetValueAsObject(EnemyActorKey.SelectedKeyName);

	if(Controller)
	{
		USBWeaponComponent* WeaponComponent = Controller->GetPawn()->FindComponentByClass<USBWeaponComponent>();
		if(WeaponComponent)
		{
			bHasName ? WeaponComponent->StartFire() : WeaponComponent->StopFire();
		}
	}
	
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
