// ShootyBooty by @GazeePuk. All Rights Reversed


#include "AI/Decorators/SBHealthDecorator.h"

#include "AIController.h"
#include "SBHealthComponent.h"

USBHealthDecorator::USBHealthDecorator()
{
	NodeName ="Health Percent";
}

bool USBHealthDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	auto const Controller = OwnerComp.GetAIOwner();
	if(!Controller) return false;

	const auto HealthComponent = Controller->GetPawn()->FindComponentByClass<USBHealthComponent>();
	if(!HealthComponent || HealthComponent->IsDead()) return false;

	return HealthComponent->GetHealthPercent() <= HealthPercent;
}
