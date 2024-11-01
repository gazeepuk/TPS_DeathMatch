// ShootyBooty by @GazeePuk. All Rights Reversed

#pragma once

#include "CoreMinimal.h"
#include "SBBaseWeapon.h"
#include "Components/ActorComponent.h"
#include "SBWeaponComponent.generated.h"
class ASBBaseWeapon;

USTRUCT(BlueprintType)
struct FWeaponData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
	TSubclassOf<ASBBaseWeapon> WeaponClass;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
	UAnimMontage* ReloadAnimMontage;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTYBOOTY_API USBWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USBWeaponComponent();

	virtual void StartFire();
	void StopFire();
	virtual void TakeNextWeapon();
	void Reload();
	
	bool GetWeaponUIData(FWeaponUIData& UIData) const;
	bool GetWeaponAmmoData(FAmmoData& AmmoData) const;
	
	bool TryToAddAmmo(TSubclassOf<ASBBaseWeapon> InWeaponType, int32 InClipsAmount);

protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	TArray<FWeaponData> WeaponData;

	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	FName WeaponEquipSocketName = "WeaponSocket";

	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	FName WeaponArmorySocketName = "ArmorySocket";
	
	UPROPERTY(EditDefaultsOnly, Category="Animation")
	UAnimMontage* EquipAnimMontage;
	

	UPROPERTY()
	ASBBaseWeapon* CurrentWeapon;

	UPROPERTY()
	TArray<ASBBaseWeapon*> Weapons;

	bool CanFire();
	bool CanEquip();
	
	void EquipWeapon(int32 WeaponIndex);
	int32 CurrentWeaponIndex = 0;
private:

	UPROPERTY()
	UAnimMontage* CurrentReloadAnimMontage = nullptr;
	
	bool bEquipAnimProgress = false;
	bool bReloadAnimProgress = false;
	
	void SpawnWeapons();
	void AttachWeaponToSocket(ASBBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName);
	void PlayAnimMotage(UAnimMontage* Animation);

	void InitAnimations();
	void OnEquipFinished(USkeletalMeshComponent* MeshComponent);
	void OnReloadFinished(USkeletalMeshComponent* MeshComponent);
	bool CanReload();

	void OnEmptyClip(ASBBaseWeapon* AmmoEmptyWeapon);
	void ChangeClip();
};
