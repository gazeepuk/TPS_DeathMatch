// ShootyBooty by @GazeePuk. All Rights Reversed


#include "Components/SBHealthComponent.h"

#include "Dev/SBFireDamageType.h"
#include "Dev/SBIceDamageType.h"
#include "GameFramework/Actor.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All)

// Sets default values for this component's properties
USBHealthComponent::USBHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USBHealthComponent::OnHealed()
{
	SetHealth(Health+HealthModifier);
	if(Health == MaxHealth && GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
	}
}


// Called when the game starts
void USBHealthComponent::BeginPlay()
{
	Super::BeginPlay();

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

	SetHealth(Health-Damage);

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
	Health = FMath::Clamp(NewHealth,0.0f,MaxHealth);
	OnHealthChanged.Broadcast(Health);
}
