// Developed by Ivan Piankouski
// GitHub / LinkedIn: gazeepuk


#include "Weapon/SBProjectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

ASBProjectile::ASBProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	CollisionComponent->InitSphereRadius(5.0f);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECR_Block);
	SetRootComponent(CollisionComponent);

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComponent");
	MovementComponent->InitialSpeed = 2500.0f;
	MovementComponent->ProjectileGravityScale = 0.2f;
}

void ASBProjectile::BeginPlay()
{
	Super::BeginPlay();

	check(MovementComponent)
	check(CollisionComponent)

	MovementComponent->Velocity = ShotDirection * MovementComponent->InitialSpeed;
	CollisionComponent->IgnoreActorWhenMoving(GetOwner(), true);

	if(HasAuthority())
	{
		CollisionComponent->OnComponentHit.AddDynamic(this, &ASBProjectile::OnProjectileHit);
		SetLifeSpan(LifeSeconds);
	}
}

void ASBProjectile::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
                                    UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!GetWorld())
	{
		return;
	}

	MovementComponent->StopMovementImmediately();

	ACharacter* OwnerCharacter = GetOwner<ACharacter>();
	AController* OwnerController = OwnerCharacter ? OwnerCharacter->GetController() : nullptr;
	UGameplayStatics::ApplyRadialDamage(GetWorld(), DamageAmount, GetActorLocation(), DamageRadius, UDamageType::StaticClass(), {}, this, GetController(), bDoFullDamage);

	DrawDebugSphere(GetWorld(), GetActorLocation(), DamageRadius, 24, FColor::Red, false, LifeSeconds);

	Destroy();
}

AController* ASBProjectile::GetController() const
{
	const auto Pawn = Cast<APawn>(GetOwner());
	return Pawn ? Pawn->GetController() : nullptr;
}
