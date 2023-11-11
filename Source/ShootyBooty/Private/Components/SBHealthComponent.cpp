// ShootyBooty by @GazeePuk. All Rights Reversed


#include "Components/SBHealthComponent.h"
#include "GameFramework/Actor.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All)

// Sets default values for this component's properties
USBHealthComponent::USBHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USBHealthComponent::OnHealed()
{
	SetHealth(CurrentHealth+HealthModifier);
	if(CurrentHealth == MaxHealth && GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
	}
}


bool USBHealthComponent::TryHeal(float HealAmount)
{
	if(IsDead() || IsHealthFull()) return false;
	SetHealth(HealAmount+CurrentHealth);
	return true;
}

// Called when the game starts
void USBHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	check(MaxHealth > 0);
	
	SetHealth(MaxHealth);
	AActor* ComponentOwner = GetOwner();
	if (ComponentOwner)
	{
		ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &USBHealthComponent::OnTakeAnyDamage);
	}
}

void USBHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
                                         AController* InstigatedBy, AActor* DamageCauser)
{
	GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);

	if (Damage <= 0 || IsDead() || !GetWorld()) return;

	SetHealth(CurrentHealth-Damage);

	if (IsDead())
	{
		OnDeath.Broadcast();
	}
	else if (bAutoHeal)
	{
		GetWorld()->GetTimerManager().SetTimer(HealTimerHandle, this, &USBHealthComponent::OnHealed,
		                                       HealthUpdateTime, true, HealthDelay);
	}
}

void USBHealthComponent::SetHealth(float NewHealth)
{
	CurrentHealth = FMath::Clamp(NewHealth,0.0f,MaxHealth);
	OnHealthChanged.Broadcast(CurrentHealth);
}
