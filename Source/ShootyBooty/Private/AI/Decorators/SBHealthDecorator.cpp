// Developed by Ivan Piankouski
// GitHub / LinkedIn: gazeepuk


#include "AI/Decorators/SBHealthDecorator.h"

#include "AIController.h"
#include "SBHealthComponent.h"

USBHealthDecorator::USBHealthDecorator()
{
	NodeName ="Health Percent";
}

bool USBHealthDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const AAIController* Controller = OwnerComp.GetAIOwner();
	if(!Controller)
	{
		return false;
	}

	const USBHealthComponent* HealthComponent = Controller->GetPawn()->FindComponentByClass<USBHealthComponent>();
	if(!HealthComponent || HealthComponent->IsDead())
	{
		return false;
	}

	return HealthComponent->GetHealthPercent() <= HealthPercent;
}
