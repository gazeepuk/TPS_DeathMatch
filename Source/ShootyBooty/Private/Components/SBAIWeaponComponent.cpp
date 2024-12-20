// Developed by Ivan Piankouski
// GitHub / LinkedIn: gazeepuk


#include "SBAIWeaponComponent.h"

void USBAIWeaponComponent::StartFire()
{
	if(!CanFire()) return;

	if(CurrentWeapon->IsAmmoEmpty())
	{
		EquipNextWeapon();
	}
	else
	{
		CurrentWeapon->StartFire();
	}
}

void USBAIWeaponComponent::EquipNextWeapon()
{
	if(!CanEquip()) return;
	int32 NextIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
	while (NextIndex != CurrentWeaponIndex)
	{
		if(!Weapons[NextIndex]->IsAmmoEmpty()) break;
		NextIndex  = (NextIndex + 1) % Weapons.Num();
	}

	if(CurrentWeaponIndex != NextIndex)
	{
		CurrentWeaponIndex = NextIndex;
		EquipWeapon(CurrentWeaponIndex);
	}
}
