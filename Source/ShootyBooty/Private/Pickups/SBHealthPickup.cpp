// ShootyBooty by @GazeePuk. All Rights Reversed


#include "Pickups/SBHealthPickup.h"

#include "SBUtils.h"

bool ASBHealthPickup::GivePickupTo(APawn* InPlayerPawn)
{
	const auto HealthComponent = USBUtils::GetHealthComponent(InPlayerPawn);
	if(!HealthComponent) return false;
	return HealthComponent->TryHeal(HealAmount);
}
