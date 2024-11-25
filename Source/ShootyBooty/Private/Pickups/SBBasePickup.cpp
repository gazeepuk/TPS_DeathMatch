// ShootyBooty by @GazeePuk. All Rights Reversed


#include "Pickups/SBBasePickup.h"
#include "Components/SphereComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogBasePickup, All, All);
ASBBasePickup::ASBBasePickup()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	CollisionComponent->InitSphereRadius(50.0f);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
	SetRootComponent(CollisionComponent);

	bReplicates = true;
}

void ASBBasePickup::BeginPlay()
{
	Super::BeginPlay();
	check(CollisionComponent)
	// Disable collision on clients
	if(!HasAuthority())
	{
		CollisionComponent->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	}
}

void ASBBasePickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if(HasAuthority())
	{
		APawn* Pawn = Cast<APawn>(OtherActor);
		if(Pawn && GivePickupTo(Pawn))
		{
			Server_OnPickupWasTaken();
		}
	}
}

bool ASBBasePickup::GivePickupTo(APawn* InPlayerPawn)
{
	return false;
}

void ASBBasePickup::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	AddMovement();
}

void ASBBasePickup::Server_OnPickupWasTaken_Implementation()
{
	CollisionComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	NetMulticast_SetVisibility(false, true);
	FTimerHandle RespawnTimerHandle;
	GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &ASBBasePickup::Server_Respawn, RespawnTime);
}

void ASBBasePickup::Server_Respawn_Implementation() const
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
	SetActorLocation(FVector3d(Location.X, Location.Y,Location.Z + FMath::Sin(GetWorld()->TimeSeconds)*0.25));
	AddActorLocalRotation(FRotator(0,0.75f,0));
}

