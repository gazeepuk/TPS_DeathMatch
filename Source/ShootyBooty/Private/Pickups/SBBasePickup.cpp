// Developed by Ivan Piankouski
// GitHub / LinkedIn: gazeepuk


#include "Pickups/SBBasePickup.h"
#include "Components/SphereComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogBasePickup, All, All);
ASBBasePickup::ASBBasePickup()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	CollisionComponent->InitSphereRadius(50.0f);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	CollisionComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	SetRootComponent(CollisionComponent);

	bReplicates = true;
}

void ASBBasePickup::BeginPlay()
{
	Super::BeginPlay();
	check(CollisionComponent)
	if(HasAuthority())
	{
		// Enable collision on Server
		CollisionComponent->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);
		CollisionComponent->SetCollisionResponseToAllChannels(ECR_Overlap);

		// Bind BeginOverlap Event
		CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnPickupCollisionBeginOverlap);
	}
}

void ASBBasePickup::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	AddMovement();
}

bool ASBBasePickup::GivePickupTo(APawn* InPlayerPawn)
{
	return false;
}

void ASBBasePickup::Respawn() const
{
	CollisionComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
	NetMulticast_SetVisibility(true, true);
}

void ASBBasePickup::NetMulticast_SetVisibility_Implementation(bool bVisible, bool bPropagateToChildren) const
{
	if(GetRootComponent())
	{
		GetRootComponent()->SetVisibility(bVisible, bPropagateToChildren);
	}
}

void ASBBasePickup::AddMovement()
{
	FVector3d Location(GetActorLocation());
	SetActorLocation(FVector3d(Location.X, Location.Y,Location.Z + FMath::Sin(GetWorld()->TimeSeconds) * 0.25f));
	AddActorLocalRotation(FRotator(0.f,0.75f,0.f));
}

void ASBBasePickup::OnPickupCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(HasAuthority())
	{
		APawn* Pawn = Cast<APawn>(OtherActor);
		if(Pawn && GivePickupTo(Pawn))
		{
			OnPickupWasTaken();
		}
	}
}

void ASBBasePickup::OnPickupWasTaken()
{
	CollisionComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	NetMulticast_SetVisibility(false, true);
	
	FTimerHandle RespawnTimerHandle;
	GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &ASBBasePickup::Respawn, RespawnTime);
}
