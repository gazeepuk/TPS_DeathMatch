// Developed by Ivan Piankouski
// GitHub / LinkedIn: gazeepuk


#include "Pickups/SBAmmoPickup.h"

#include "SBUtils.h"


bool ASBAmmoPickup::GivePickupTo(APawn* InPlayerPawn)
{
	const auto HealthComponent = USBUtils::GetHealthComponent(InPlayerPawn);
	if(!HealthComponent || HealthComponent->IsDead())
	{
		return false;
	}

	USBWeaponComponent* WeaponComponent = USBUtils::GetWeaponComponent(InPlayerPawn);
	if(!WeaponComponent)
	{
		return false;
	}
	
	return WeaponComponent->TryToAddAmmo(WeaponType, ClipsAmount);
}
