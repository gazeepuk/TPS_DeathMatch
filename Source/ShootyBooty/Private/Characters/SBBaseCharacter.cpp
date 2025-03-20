// Developed by Ivan Piankouski
// GitHub / LinkedIn: gazeepuk


#include "SBBaseCharacter.h"
#include "SBCharacterMovementComponent.h"
#include "SBHealthComponent.h"
#include "SBWeaponComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/DamageEvents.h"
#include "GameModes/DeathMatchGameMode.h"

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

	// Callbacks of these Delegates Run on Server
	if(HasAuthority())
	{
		HealthComponent->OnDeath.AddUObject(this, &ASBBaseCharacter::OnDeath);
		LandedDelegate.AddDynamic(this, &ASBBaseCharacter::OnGroundLanded);
	}

	// Callbacks of these Delegates Run on Owning Client
	HealthComponent->OnHealthChanged.AddUObject(this, &ASBBaseCharacter::OnHealthChanged);
	OnHealthChanged(HealthComponent->GetHealth());
	
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

//Runs on Server
void ASBBaseCharacter::OnDeath()
{
	UE_LOG(LogBaseCharacterLog, Error, TEXT("Player %s is dead"),*GetName())

	NetMulticast_OnDeath();

	GetWorldTimerManager().ClearTimer(RespawnTimerHandle);
	GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &ASBBaseCharacter::Respawn, RespawnDelay);
}

//Runs on Server and Clients
void ASBBaseCharacter::NetMulticast_OnDeath_Implementation()
{
	PlayAnimMontage(DeathAnimMontage);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	HealthTextComponent->SetVisibility(false);

	GetCharacterMovement()->StopMovementImmediately();
	GetCharacterMovement()->DisableMovement();
	DisableInput(GetController<APlayerController>());
}

void ASBBaseCharacter::OnHealthChanged(const float Health) const
{
	HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));
}

void ASBBaseCharacter::Respawn()
{
	if(!HasAuthority())
	{
		return;
	}
	
	ADeathMatchGameMode* DeathMatchGameMode = GetWorld()->GetAuthGameMode<ADeathMatchGameMode>();
	if(DeathMatchGameMode)
	{
		DeathMatchGameMode->RespawnPlayer(this, GetController());
	}
}

//Calculating and applying falling damage
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


