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

	HealthTextComponent = CreateDefaultSubobject<UTextRenderComponent>("TextRenderComponent");
	HealthTextComponent->SetupAttachment(GetRootComponent());
	HealthTextComponent->SetOwnerNoSee(true);

	WeaponComponent = CreateDefaultSubobject<USBWeaponComponent>("WeaponComponent");
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


void ASBBaseCharacter::OnDeath()
{
	UE_LOG(LogBaseCharacterLog, Error, TEXT("Player %s is dead"),*GetName())

	PlayAnimMontage(DeathAnimMontage);
	GetCharacterMovement()->DisableMovement();

	SetLifeSpan(5.0f);

	if(Controller)
	{
		Controller->ChangeState(NAME_Spectating);
	}
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Ignore);
	WeaponComponent->StopFire();
}

void ASBBaseCharacter::OnHealthChanged(float Health)
{
	HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));
}


void ASBBaseCharacter::OnGroundLanded(const FHitResult& Hit)
{
	const auto FallVelocityZ = GetCharacterMovement()->Velocity.Z * -1;
	UE_LOG(LogBaseCharacterLog, Warning, TEXT("Landed. Velocity Z: %f"),FallVelocityZ)

	if(FallVelocityZ<LandedDamageVelocity.X)
	{
		return;
	}

	const auto FinalDamage = FMath::GetMappedRangeValueClamped(LandedDamageVelocity,LandedDamage,FallVelocityZ);
	UE_LOG(LogBaseCharacterLog, Warning, TEXT("FinalDamage: %f"),FinalDamage)
	TakeDamage(FinalDamage, FDamageEvent{},nullptr, nullptr);
}


