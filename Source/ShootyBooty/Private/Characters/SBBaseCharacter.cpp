// ShootyBooty by @GazeePuk. All Rights Reversed


#include "SBBaseCharacter.h"
#include "SBCharacterMovementComponent.h"
#include "SBHealthComponent.h"
#include "SBWeaponComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/DamageEvents.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseCharacterLog, All, All);

ASBBaseCharacter::ASBBaseCharacter(const FObjectInitializer& ObjInit)
	: Super(ObjInit.SetDefaultSubobjectClass<USBCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = false;

	HealthComponent = CreateDefaultSubobject<USBHealthComponent>("HealthComponent");
	HealthComponent->SetIsReplicated(true);

	HealthTextComponent = CreateDefaultSubobject<UTextRenderComponent>("TextRenderComponent");
	HealthTextComponent->SetupAttachment(GetRootComponent());
	HealthTextComponent->SetOwnerNoSee(true);

	WeaponComponent = CreateDefaultSubobject<USBWeaponComponent>("WeaponComponent");
	WeaponComponent->SetIsReplicated(true);

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
}

// Called when the game starts or when spawned
void ASBBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(HealthComponent);
	check(HealthTextComponent);
	check(GetCharacterMovement());

	OnHealthChanged(HealthComponent->GetHealth());
	HealthComponent->OnDeath.AddUObject(this, &ASBBaseCharacter::OnDeath);
	HealthComponent->OnHealthChanged.AddUObject(this, &ASBBaseCharacter::OnHealthChanged);
	
	LandedDelegate.AddDynamic(this, &ASBBaseCharacter::OnGroundLanded);
} 

bool ASBBaseCharacter::IsRunning() const
{
	return bWantsToRun && bMovingForward && !GetVelocity().IsZero();
}

float ASBBaseCharacter::GetMoveDirection() const
{
	if (GetVelocity().IsZero()) return 0.0f;
	const FVector VelocityNormal = GetVelocity().GetSafeNormal();
	const float AngelBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));
	const FVector CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);
	const float Degrees = FMath::RadiansToDegrees(AngelBetween);
	return CrossProduct.IsZero() ? Degrees : Degrees * FMath::Sign(CrossProduct.Z);
}

//Plays animation montages on Server and Clients
void ASBBaseCharacter::NetMulticast_PlayAnimMontage_Implementation(UAnimMontage* AnimMontage, const float PlayRate)
{
	PlayAnimMontage(AnimMontage, PlayRate);
}

//Run on Server
void ASBBaseCharacter::OnDeath()
{
	UE_LOG(LogBaseCharacterLog, Error, TEXT("Player %s is dead"),*GetName())

	NetMulticast_PlayAnimMontage(DeathAnimMontage);
	GetCharacterMovement()->DisableMovement();

	SetLifeSpan(5.0f);
	
	NetMulticast_OnDeath();
}

//Runs on Server and Clients
void ASBBaseCharacter::NetMulticast_OnDeath_Implementation()
{
	if(Controller)
	{
		Controller->ChangeState(NAME_Spectating);
	}
	
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Ignore);
	WeaponComponent->StopFire();
}

void ASBBaseCharacter::OnHealthChanged(const float Health) const
{
	HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));
}


void ASBBaseCharacter::OnGroundLanded(const FHitResult& Hit)
{
	if(HasAuthority())
	{
		const float FallVelocityZ = GetCharacterMovement()->Velocity.Z * -1;
		UE_LOG(LogBaseCharacterLog, Warning, TEXT("Landed. Velocity Z: %f"),FallVelocityZ)

		if(FallVelocityZ < LandedDamageVelocity.X)
		{
			return;
		}

		const float FinalDamage = FMath::GetMappedRangeValueClamped(LandedDamageVelocity,LandedDamage,FallVelocityZ);
		UE_LOG(LogBaseCharacterLog, Warning, TEXT("FinalDamage: %f"),FinalDamage)

		TakeDamage(FinalDamage, FDamageEvent{},nullptr, nullptr);
	}
}


