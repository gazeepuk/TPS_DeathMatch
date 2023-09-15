// ShootyBooty by @GazeePuk. All Rights Reversed


#include "UI/SBPlayerHUDWidget.h"

#include "SBHealthComponent.h"
#include "SBWeaponComponent.h"

float USBPlayerHUDWidget::GetHealthPercent() const
{

	const auto HealthComponent = GetHealthComponent();
	if(!HealthComponent) return 0.0f;

	return HealthComponent->GetHealthPercent();
}

bool USBPlayerHUDWidget::GetWeaponUIData(FWeaponUIData& UIData)
{
	const auto WeaponComponent = GetWeaponComponent();
	if(!WeaponComponent) return 0.0f;

	return WeaponComponent->GetWeaponUIData(UIData);
}

bool USBPlayerHUDWidget::GetWeaponAmmoData(FAmmoData& AmmoData)
{
	const auto WeaponComponent = GetWeaponComponent();
	if(!WeaponComponent) return false;

	return WeaponComponent->GetWeaponAmmoData(AmmoData);
}

bool USBPlayerHUDWidget::IsPlayerAlive() const
{
	const auto HealthComponent = GetHealthComponent();
	return HealthComponent && !HealthComponent->IsDead();
}

bool USBPlayerHUDWidget::IsPlayerSpectating() const
{
	const auto Controller = GetOwningPlayer();
	return Controller && Controller->GetStateName() == NAME_Spectating;
}

USBWeaponComponent* USBPlayerHUDWidget::GetWeaponComponent() const
{
	const auto Player = GetOwningPlayerPawn();
	if(!Player) return nullptr;

	const auto WeaponComponent = Player->GetComponentByClass<USBWeaponComponent>();
	return WeaponComponent;
}

USBHealthComponent* USBPlayerHUDWidget::GetHealthComponent() const
{
	const auto Player = GetOwningPlayerPawn();
	if(!Player) return nullptr;

	const auto HealthComponent = Player->GetComponentByClass<USBHealthComponent>();
	return HealthComponent;
}
