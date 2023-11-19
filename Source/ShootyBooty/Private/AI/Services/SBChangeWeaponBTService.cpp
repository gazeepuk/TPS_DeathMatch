// ShootyBooty by @GazeePuk. All Rights Reversed


#include "AI/Services/SBChangeWeaponBTService.h"

#include "AIController.h"
#include "SBWeaponComponent.h"

USBChangeWeaponBTService::USBChangeWeaponBTService()
{
	NodeName = "Change Weapon";
}

void USBChangeWeaponBTService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Controller = OwnerComp.GetAIOwner();
	if(Controller)
	{
		const auto WeaponComponent = Controller->GetPawn()->FindComponentByClass<USBWeaponComponent>();
		if(WeaponComponent && Probability > 0 && FMath::FRand() <= Probability)
		{
			WeaponComponent->NextWeapon();
		}
	}
	
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
