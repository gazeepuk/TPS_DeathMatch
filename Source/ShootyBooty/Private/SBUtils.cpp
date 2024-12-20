// Developed by Ivan Piankouski
// GitHub / LinkedIn: gazeepuk


#include "SBUtils.h"

USBWeaponComponent* USBUtils::GetWeaponComponent(const APawn* InPlayerPawn)
{
	if(!InPlayerPawn) return nullptr;

	const auto WeaponComponent = InPlayerPawn->GetComponentByClass<USBWeaponComponent>();
	return WeaponComponent;
}

USBHealthComponent* USBUtils::GetHealthComponent(const AActor* InPlayerPawn)
{
	if(!InPlayerPawn) return nullptr;

	const auto HealthComponent = InPlayerPawn->GetComponentByClass<USBHealthComponent>();
	return HealthComponent;
}
