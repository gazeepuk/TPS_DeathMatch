// ShootyBooty by @GazeePuk. All Rights Reversed


#include "Weapon/SBWeaponComponent.h"

#include "AnimUtils.h"
#include "SBBaseWeapon.h"
#include "SBEquipFinishAnimNotify.h"
#include "SBReloadFinishedAnimNotify.h"
#include "GameFramework/Character.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeaponComponent, All, All)

USBWeaponComponent::USBWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USBWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentWeaponIndex = 0;
	SpawnWeapons();
	EquipWeapon(CurrentWeaponIndex);
	InitAnimations();
}

void USBWeaponComponent::StartFire()
{
	if (!CanFire()) return;
	CurrentWeapon->StartFire();
}

void USBWeaponComponent::StopFire()
{
	if (!CurrentWeapon) return;
	CurrentWeapon->StopFire();
}

void USBWeaponComponent::NextWeapon()
{
	if (!CanEquip()) return;

	CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
	EquipWeapon(CurrentWeaponIndex);
}

void USBWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	CurrentWeapon = nullptr;
	for (auto Weapon : Weapons)
	{
		Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		Weapon->Destroy();
	}
	Weapons.Empty();

	Super::EndPlay(EndPlayReason);
}


void USBWeaponComponent::SpawnWeapons()
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character || !GetWorld()) return;

	for (auto WeaponDatum : WeaponData)
	{
		auto Weapon = GetWorld()->SpawnActor<ASBBaseWeapon>(WeaponDatum.WeaponClass);
		if (!Weapon) continue;

		Weapon->OnClipEmpty.AddUObject(this, &USBWeaponComponent::OnEmptyClip);
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
	if (WeaponIndex < 0 || WeaponIndex >= Weapons.Num())
	{
		UE_LOG(LogWeaponComponent, Error, TEXT("Invalid Weapon Index"));
		return;
	}
	if (Weapons.Num() <= 0) return;
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character) return;

	if (CurrentWeapon)
	{
		CurrentWeapon->StopFire();
		AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponArmorySocketName);
	}

	CurrentWeapon = Weapons[WeaponIndex];

	const auto CurrentWeaponData = WeaponData.FindByPredicate([&](const FWeaponData Data)
	{
		return Data.WeaponClass == CurrentWeapon->GetClass();
	});

	CurrentReloadAnimMontage = CurrentWeaponData ? CurrentWeaponData->ReloadAnimMontage : nullptr;

	AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponEquipSocketName);
	bEquipAnimProgress = true;
	PlayAnimMotage(EquipAnimMontage);
}

void USBWeaponComponent::Reload()
{
	ChangeClip();
}

bool USBWeaponComponent::GetWeaponUIData(FWeaponUIData& UIData) const
{
	if(CurrentWeapon)
	{
		UIData = CurrentWeapon->GetUIData();
		return true;
	}
	return false;
}

bool USBWeaponComponent::GetWeaponAmmoData(FAmmoData& AmmoData) const
{
	if(CurrentWeapon)
	{
		AmmoData = CurrentWeapon->GetAmmoData();
		return true;
	}
	return false;
}

void USBWeaponComponent::PlayAnimMotage(UAnimMontage* Animation)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character) return;

	Character->PlayAnimMontage(Animation);
}

void USBWeaponComponent::InitAnimations()
{
	auto EquipFinishedNotify = AnimUtils::FindNotifyByClass<USBEquipFinishAnimNotify>(EquipAnimMontage);
	if (EquipFinishedNotify)
	{
		EquipFinishedNotify->OnNotified.AddUObject(this, &USBWeaponComponent::OnEquipFinished);
	}

	for (auto WeaponDatum : WeaponData)
	{
		auto ReloadFinishedNotify = AnimUtils::FindNotifyByClass<USBReloadFinishedAnimNotify>(WeaponDatum.ReloadAnimMontage);
		if (!ReloadFinishedNotify) continue;
		
		ReloadFinishedNotify->OnNotified.AddUObject(this, &USBWeaponComponent::OnReloadFinished);
	}
}

void USBWeaponComponent::OnEquipFinished(USkeletalMeshComponent* MeshComponent)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());

	if (!Character || Character->GetMesh() != MeshComponent)
	{
	}
	bEquipAnimProgress = false;
}

void USBWeaponComponent::OnReloadFinished(USkeletalMeshComponent* MeshComponent)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());

	if (!Character || Character->GetMesh() != MeshComponent)
	{
	}
	bReloadAnimProgress = false;
}

bool USBWeaponComponent::CanReload()
{
	return CurrentWeapon && !bEquipAnimProgress && !bReloadAnimProgress && CurrentWeapon->CanReload();
}

void USBWeaponComponent::OnEmptyClip()
{
	ChangeClip();
}

void USBWeaponComponent::ChangeClip()
{
	if (!CanReload()) return;
	CurrentWeapon->StopFire();
	CurrentWeapon->ChangeClip();
	bReloadAnimProgress = true;
	PlayAnimMotage(CurrentReloadAnimMontage);
}

bool USBWeaponComponent::CanFire()
{
	return CurrentWeapon && !bEquipAnimProgress && !bReloadAnimProgress;
}

bool USBWeaponComponent::CanEquip()
{
	return !bEquipAnimProgress && !bReloadAnimProgress;
}
