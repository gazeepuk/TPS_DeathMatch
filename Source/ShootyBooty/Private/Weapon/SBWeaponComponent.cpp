// ShootyBooty by @GazeePuk. All Rights Reversed


#include "Weapon/SBWeaponComponent.h"
#include "SBBaseWeapon.h"
#include "GameFramework/Character.h"


USBWeaponComponent::USBWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USBWeaponComponent::StartFire()
{
	if (!CurrentWeapon) return;
	CurrentWeapon->StartFire();
}

void USBWeaponComponent::StopFire()
{
	if (!CurrentWeapon) return;
	CurrentWeapon->StopFire();
}

void USBWeaponComponent::NextWeapon()
{
	CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
	EquipWeapon(CurrentWeaponIndex);
}


void USBWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentWeaponIndex = 0;
	SpawnWeapons();
	EquipWeapon(CurrentWeaponIndex);
}


void USBWeaponComponent::SpawnWeapons()
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character || !GetWorld()) return;

	for (auto WeaponClass : WeaponClasses)
	{
		auto Weapon = GetWorld()->SpawnActor<ASBBaseWeapon>(WeaponClass);
		if (!Weapon) continue;
		Weapon->SetOwner(Character);
		Weapons.Add(Weapon);

		AttachWeaponToSocket(Weapon, Character->GetMesh(), WeaponArmorySocketName);
	}
}

void USBWeaponComponent::AttachWeaponToSocket(ASBBaseWeapon* Weapon, USceneComponent* SceneComponent,
                                              const FName& SocketName)
{
	if (!Weapon || !SceneComponent) return;
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	Weapon->AttachToComponent(SceneComponent, AttachmentRules, SocketName);
}

void USBWeaponComponent::EquipWeapon(int32 WeaponIndex)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character) return;

	if (CurrentWeapon)
	{
		AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponArmorySocketName);
	}

	CurrentWeapon = Weapons[WeaponIndex];
	AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponEquipSocketName);
}
