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
}

void ASBBasePickup::BeginPlay()
{
	Super::BeginPlay();
	check(CollisionComponent)
}

void ASBBasePickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	const auto Pawn = Cast<APawn>(OtherActor);
	if(Pawn && GivePickupTo(Pawn))
	{
		OnPickupWasTaken();
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

void ASBBasePickup::OnPickupWasTaken()
{
	CollisionComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	if(GetRootComponent())
		GetRootComponent()->SetVisibility(false,true);
	FTimerHandle RespawnTimerHandle;
	GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &ASBBasePickup::Respawn, RespawnTime);
}

void ASBBasePickup::Respawn()
{
	CollisionComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
	if(GetRootComponent())
		GetRootComponent()->SetVisibility(true,true);
}

void ASBBasePickup::AddMovement()
{
	FVector3d Location(GetActorLocation());
	SetActorLocation(FVector3d(Location.X, Location.Y,Location.Z + FMath::Sin(GetWorld()->TimeSeconds)*0.25));
	AddActorLocalRotation(FRotator(0,0.75f,0));
}

