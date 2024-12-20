// Developed by Ivan Piankouski
// GitHub / LinkedIn: gazeepuk


#include "AI/Services/SBChangeWeaponBTService.h"

#include "AIController.h"
#include "SBWeaponComponent.h"

USBChangeWeaponBTService::USBChangeWeaponBTService()
{
	NodeName = "Change Weapon";
}

void USBChangeWeaponBTService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const AAIController* Controller = OwnerComp.GetAIOwner();
	if(Controller)
	{
		USBWeaponComponent* WeaponComponent = Controller->GetPawn()->FindComponentByClass<USBWeaponComponent>();
		if(WeaponComponent && Probability > 0 && FMath::FRand() <= Probability)
		{
			WeaponComponent->EquipNextWeapon();
		}
	}
	
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
