// ShootyBooty by @GazeePuk. All Rights Reversed


#include "UI/SBPlayerHUDWidget.h"

#include "SBHealthComponent.h"
#include "SBUtils.h"
#include "SBWeaponComponent.h"
#include "Components/TextBlock.h"

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

void USBPlayerHUDWidget::SetCountdownText(float CountdownTime) const
{
	CountdownTime = FMath::Max(CountdownTime, 0.f);
	int32 Minutes = FMath::FloorToInt(CountdownTime / 60.f);
	int32 Seconds = CountdownTime - Minutes * 60;
	FString CountdownText = FString::Printf(TEXT("%02d:%02d"), Minutes, Seconds);
	MatchCountdownTextBlock->SetText(FText::FromString(CountdownText));
}

void USBPlayerHUDWidget::SetCountdownText(const FText& CountdownText) const
{
	MatchCountdownTextBlock->SetText(CountdownText);
}
