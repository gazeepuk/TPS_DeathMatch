// Developed by Ivan Piankouski
// GitHub / LinkedIn: gazeepuk


#include "SBWeaponComponent.h"

#include "AnimUtils.h"
#include "SBBaseWeapon.h"
#include "SBEquipFinishAnimNotify.h"
#include "SBReloadFinishedAnimNotify.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeaponComponent, All, All)

USBWeaponComponent::USBWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USBWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	//Spawns and equips weapons on server
	if(GetOwner()->HasAuthority())
	{
		CurrentWeaponIndex = 0;
		SpawnWeapons();
		EquipWeapon(CurrentWeaponIndex);
		InitAnimations();
	}
}

void USBWeaponComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, CurrentWeaponIndex);
	DOREPLIFETIME(ThisClass, CurrentWeapon);
	DOREPLIFETIME(ThisClass, Weapons);
}

void USBWeaponComponent::StartFire()
{
	if (!CanFire())
	{
		return;
	}
	CurrentWeapon->StartFire();
}

void USBWeaponComponent::StopFire() const
{
	if (!CurrentWeapon)
	{
		return;
	}
	CurrentWeapon->StopFire();
}

void USBWeaponComponent::EquipNextWeapon()
{
	if (!CanEquip()) return;

	CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
	EquipWeapon(CurrentWeaponIndex);
}

void USBWeaponComponent::EquipWeapon(int32 WeaponIndex)
{
	if (WeaponIndex < 0 || WeaponIndex >= Weapons.Num())
	{
		UE_LOG(LogWeaponComponent, Error, TEXT("Invalid Weapon Index"));
		return;
	}
	if (Weapons.Num() <= 0)
	{
		return;
	}
	
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character)
	{
		return;
	}

	if (CurrentWeapon)
	{
		CurrentWeapon->StopFire();
		AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponArmorySocketName);
	}

	CurrentWeapon = Weapons[WeaponIndex];

	const FWeaponData* CurrentWeaponData = WeaponData.FindByPredicate([&](const FWeaponData Data)
	{
		return Data.WeaponClass == CurrentWeapon->GetClass();
	});

	CurrentReloadAnimMontage = CurrentWeaponData ? CurrentWeaponData->ReloadAnimMontage : nullptr;

	AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponEquipSocketName);
	bEquipAnimProgress = true;
	NetMulticast_PlayAnimMontage(EquipAnimMontage, 1.f);
}

void USBWeaponComponent::Server_EndPlay_Implementation()
{
	CurrentWeapon = nullptr;
	for (ASBBaseWeapon* Weapon : Weapons)
	{
		Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		Weapon->Destroy();
	}
	Weapons.Empty();
}

void USBWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if(GetOwner()->HasAuthority())
	{
		CurrentWeapon = nullptr;
		for (ASBBaseWeapon* Weapon : Weapons)
		{
			Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
			Weapon->Destroy();
		}
		Weapons.Empty();
	}
	Server_EndPlay();

	Super::EndPlay(EndPlayReason);
}

void USBWeaponComponent::SpawnWeapons()
{
	if(!GetOwner()->HasAuthority())
	{
		return;
	}
	
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character || !GetWorld())
	{
		return;
	}

	for (const FWeaponData& WeaponDatum : WeaponData)
	{
		ASBBaseWeapon* Weapon = GetWorld()->SpawnActor<ASBBaseWeapon>(WeaponDatum.WeaponClass);
		if (!Weapon)
		{
			continue;
		}

		Weapon->OnClipEmpty.AddUObject(this, &USBWeaponComponent::OnEmptyClip);
		Weapon->SetOwner(Character);
		Weapons.Add(Weapon);

		AttachWeaponToSocket(Weapon, Character->GetMesh(), WeaponArmorySocketName);
	}
}

void USBWeaponComponent::AttachWeaponToSocket(ASBBaseWeapon* Weapon, USceneComponent* SceneComponent,
                                              const FName& SocketName)
{
	if (!Weapon || !SceneComponent)
	{
		return;
	}
	
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	Weapon->AttachToComponent(SceneComponent, AttachmentRules, SocketName);
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

bool USBWeaponComponent::TryToAddAmmo(TSubclassOf<ASBBaseWeapon> InWeaponType, int32 InClipsAmount)
{
	for (ASBBaseWeapon* Weapon : Weapons)
	{
		if(Weapon && Weapon->IsA(InWeaponType))
		{
			return Weapon->TryToAddAmmo(InClipsAmount);
		}
	}
	return false;
}
void USBWeaponComponent::Server_PlayAnimMontage_Implementation(UAnimMontage* Animation, float PlayRate)
{
	NetMulticast_PlayAnimMontage(Animation, PlayRate);
}

void USBWeaponComponent::NetMulticast_PlayAnimMontage_Implementation(UAnimMontage* Animation, float PlayRate)
{
	PlayAnimMontage(Animation, PlayRate);
}

void USBWeaponComponent::PlayAnimMontage(UAnimMontage* Animation, float PlayRate) const
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character)
	{
		return;
	}

	Character->PlayAnimMontage(Animation);
}

void USBWeaponComponent::InitAnimations()
{
	USBEquipFinishAnimNotify* EquipFinishedNotify = AnimUtils::FindNotifyByClass<USBEquipFinishAnimNotify>(EquipAnimMontage);
	if (EquipFinishedNotify)
	{
		EquipFinishedNotify->OnNotified.AddUObject(this, &USBWeaponComponent::OnEquipFinished);
	}

	for (const FWeaponData& WeaponDatum : WeaponData)
	{
		USBReloadFinishedAnimNotify* ReloadFinishedNotify = AnimUtils::FindNotifyByClass<USBReloadFinishedAnimNotify>(WeaponDatum.ReloadAnimMontage);
		if (!ReloadFinishedNotify)
		{
			continue;
		}
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

bool USBWeaponComponent::CanReload() const
{
	return CurrentWeapon && !bEquipAnimProgress && !bReloadAnimProgress && CurrentWeapon->CanReload();
}

void USBWeaponComponent::OnEmptyClip(ASBBaseWeapon* AmmoEmptyWeapon)
{
	if(!AmmoEmptyWeapon) return;
	if(CurrentWeapon == AmmoEmptyWeapon)
	{
		ChangeClip();
	}
	else
	{
		for(const auto Weapon : Weapons)
		{
			if(Weapon == AmmoEmptyWeapon)
			{
				Weapon->ChangeClip();
			}
		}
	}
	ChangeClip();
}

void USBWeaponComponent::ChangeClip()
{
	if (!CanReload()) return;
	CurrentWeapon->StopFire();
	CurrentWeapon->ChangeClip();
	bReloadAnimProgress = true;
	NetMulticast_PlayAnimMontage(CurrentReloadAnimMontage, 1.f);
}

bool USBWeaponComponent::CanFire() const
{
	return CurrentWeapon && !bEquipAnimProgress && !bReloadAnimProgress;
}

bool USBWeaponComponent::CanEquip() const
{
	return !bEquipAnimProgress && !bReloadAnimProgress;
}
