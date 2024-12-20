// Developed by Ivan Piankouski
// GitHub / LinkedIn: gazeepuk


#include "Dev/SBDevDamageActor.h"

#include "Kismet/GameplayStatics.h"

ASBDevDamageActor::ASBDevDamageActor()
{
	PrimaryActorTick.bCanEverTick = true;

	CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);
}

void ASBDevDamageActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DrawDebugSphere(GetWorld(), GetActorLocation(), Radius, 24, SphereColor);

	UGameplayStatics::ApplyRadialDamage(GetWorld(), Damage, GetActorLocation(),Radius, DamageType, {}, this, nullptr, DoFullDamage);
}


