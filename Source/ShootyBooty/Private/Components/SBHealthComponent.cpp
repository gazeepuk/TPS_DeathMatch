// Developed by Ivan Piankouski
// GitHub / LinkedIn: gazeepuk


#include "Components/SBHealthComponent.h"

#include "SBPlayerCharacter.h"
#include "Controllers/DeathMatchPlayerController.h"
#include "GameFramework/Actor.h"
#include "GameModes/DeathMatchGameMode.h"
#include "Net/UnrealNetwork.h"

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

	//Set default health and assign to OnTakeAnyDamage owner's delegate on the Server
	if(GetOwner()->HasAuthority())
	{
		check(MaxHealth > 0);

		SetHealth(MaxHealth);
		
		AActor* ComponentOwner = GetOwner();
		if (ComponentOwner)
		{
			ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &USBHealthComponent::OnTakeAnyDamage);
		}
	}
}

void USBHealthComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, CurrentHealth);
}

//Runs on the Server
void USBHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
                                         AController* InstigatedBy, AActor* DamageCauser)
{
	GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);

	if (Damage <= 0 || IsDead() || !GetWorld())
	{
		return;
	}

	SetHealth(CurrentHealth - Damage);
	
	
	if (IsDead())
	{
		ADeathMatchGameMode* DeathMatchGameMode = GetWorld()->GetAuthGameMode<ADeathMatchGameMode>();
		if(DeathMatchGameMode)
		{
			ASBPlayerCharacter* OwningCharacter = GetOwner<ASBPlayerCharacter>();
			ADeathMatchPlayerController* VictimController = OwningCharacter ? OwningCharacter->GetController<ADeathMatchPlayerController>() : nullptr;
			ADeathMatchPlayerController* AttackerController = InstigatedBy ? Cast<ADeathMatchPlayerController>(InstigatedBy) : nullptr;
			DeathMatchGameMode->PlayerEliminated(GetOwner<ASBPlayerCharacter>(), VictimController, AttackerController);
		}
		
		//OnDeath.Broadcast();
	}
	
	else if (bAutoHeal)
	{
		GetWorld()->GetTimerManager().SetTimer(HealTimerHandle, this, &USBHealthComponent::OnHealed,HealthUpdateTime, true, HealthDelay);
	}
}


void USBHealthComponent::SetHealth(const float NewHealth)
{
	CurrentHealth = FMath::Clamp(NewHealth,0.0f,MaxHealth);
	OnHealthChanged.Broadcast(CurrentHealth);
}

void USBHealthComponent::OnRep_CurrentHealth(float OldCurrentHealth) const
{
	if (IsDead() || !GetWorld())
	{
		return;
	}

	//Broadcast health delegates to a client 
	OnHealthChanged.Broadcast(CurrentHealth);
}
