// ShootyBooty by @GazeePuk. All Rights Reversed


#include "UI/SBPlayerHUDWidget.h"

#include "SBHealthComponent.h"
#include "SBUtils.h"
#include "SBWeaponComponent.h"

float USBPlayerHUDWidget::GetHealthPercent() const
{

	const auto HealthComponent = USBUtils::GetHealthComponent(GetOwningPlayerPawn());
	if(!HealthComponent) return 0.0f;

	return HealthComponent->GetHealthPercent();
}

bool USBPlayerHUDWidget::GetWeaponUIData(FWeaponUIData& UIData)
{
	const auto WeaponComponent = USBUtils::GetWeaponComponent(GetOwningPlayerPawn());
	if(!WeaponComponent) return 0.0f;

	return WeaponComponent->GetWeaponUIData(UIData);
}

bool USBPlayerHUDWidget::GetWeaponAmmoData(FAmmoData& AmmoData)
{
	const auto WeaponComponent = USBUtils::GetWeaponComponent(GetOwningPlayerPawn());
	if(!WeaponComponent) return false;

	return WeaponComponent->GetWeaponAmmoData(AmmoData);
}

bool USBPlayerHUDWidget::IsPlayerAlive() const
{
	const auto HealthComponent = USBUtils::GetHealthComponent(GetOwningPlayerPawn());
	return HealthComponent && !HealthComponent->IsDead();
}

bool USBPlayerHUDWidget::IsPlayerSpectating() const
{
	const auto Controller = GetOwningPlayer();
	return Controller && Controller->GetStateName() == NAME_Spectating;
}
