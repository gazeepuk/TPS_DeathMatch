// ShootyBooty by @GazeePuk. All Rights Reversed


#include "Weapon/SBBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"

ASBBaseWeapon::ASBBaseWeapon()
{
	PrimaryActorTick.bCanEverTick = false;
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	SetRootComponent(WeaponMesh);

}

void ASBBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}


