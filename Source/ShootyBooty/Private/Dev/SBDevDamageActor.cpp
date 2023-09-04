// ShootyBooty by @GazeePuk. All Rights Reversed


#include "Dev/SBDevDamageActor.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
ASBDevDamageActor::ASBDevDamageActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);
}

// Called when the game starts or when spawned
void ASBDevDamageActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASBDevDamageActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DrawDebugSphere(GetWorld(), GetActorLocation(), Radius, 24, SphereColor);

	UGameplayStatics::ApplyRadialDamage(GetWorld(), Damage, GetActorLocation(),Radius, DamageType, {}, this, nullptr, DoFullDamage);
}


