// ShootyBooty by @GazeePuk. All Rights Reversed


#include "Weapon/SBWeaponComponent.h"
#include "SBBaseWeapon.h"
#include "GameFramework/Character.h"


USBWeaponComponent::USBWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void USBWeaponComponent::Fire()
{
	if(!CurrentWeapon) return;
	CurrentWeapon->Fire();
}


void USBWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	SpawnWeapon();
}


void USBWeaponComponent::SpawnWeapon()
{
	if(!GetWorld()) return;
	CurrentWeapon = GetWorld()->SpawnActor<ASBBaseWeapon>(WeaponClass);
	if(CurrentWeapon)
	{
		ACharacter* Character = Cast<ACharacter>(GetOwner());
		if(!Character) return;
		
		FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget,false);
		CurrentWeapon->AttachToComponent( Character->GetMesh(), AttachmentRules, WeaponAttachPointName);
		CurrentWeapon->SetOwner(Character);
	}
}
