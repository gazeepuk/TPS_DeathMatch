// ShootyBooty by @GazeePuk. All Rights Reversed


#include "Components/SBHealthComponent.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
USBHealthComponent::USBHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void USBHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;

	AActor* ComponentOwner = GetOwner();
	if (ComponentOwner)
	{
		ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &USBHealthComponent::OnTakeAnyDamage);
	}
}

void USBHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
                                               AController* InstigatedBy, AActor* DamageCauser)
{
	Health -= Damage;
}
