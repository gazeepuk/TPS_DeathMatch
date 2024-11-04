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
	void StopFire() const;
	virtual void EquipNextWeapon();
	void Reload();
	
	bool GetWeaponUIData(FWeaponUIData& UIData) const;
	bool GetWeaponAmmoData(FAmmoData& AmmoData) const;
	
	bool TryToAddAmmo(TSubclassOf<ASBBaseWeapon> InWeaponType, int32 InClipsAmount);

protected:
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	UFUNCTION(Server,Reliable)
	void Server_EndPlay();
	
	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	TArray<FWeaponData> WeaponData;

	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	FName WeaponEquipSocketName = "WeaponSocket";

	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	FName WeaponArmorySocketName = "ArmorySocket";
	
	UPROPERTY(EditDefaultsOnly, Category="Animation")
	UAnimMontage* EquipAnimMontage;
	

	UPROPERTY(Replicated)
	ASBBaseWeapon* CurrentWeapon;

	UPROPERTY(Replicated)
	TArray<ASBBaseWeapon*> Weapons;

	bool CanFire() const;
	bool CanEquip() const;

	UFUNCTION(Server, Reliable)
	void Server_EquipWeapon(int32 WeaponIndex);
	void EquipWeapon(int32 WeaponIndex);

	UPROPERTY(Replicated)
	int32 CurrentWeaponIndex = 0;
private:

	UPROPERTY()
	UAnimMontage* CurrentReloadAnimMontage = nullptr;

	bool bEquipAnimProgress = false;
	bool bReloadAnimProgress = false;

	//Spawning Weapon in world
	UFUNCTION(Server, Reliable)
	void Server_SpawnWeapons();
	void SpawnWeapons();

	//Attaching weapon to owner socket
	void AttachWeaponToSocket(ASBBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName);

	//Playing Animation Montage
	UFUNCTION(Server, Unreliable)
	void Server_PlayAnimMontage(UAnimMontage* Animation, float PlayRate);
	UFUNCTION(NetMulticast, Unreliable)
	void NetMulticast_PlayAnimMontage(UAnimMontage* Animation, float PlayRate);
	void PlayAnimMontage(UAnimMontage* Animation, float PlayRate) const;

	void InitAnimations();
	void OnEquipFinished(USkeletalMeshComponent* MeshComponent);
	void OnReloadFinished(USkeletalMeshComponent* MeshComponent);
	bool CanReload() const;

	void OnEmptyClip(ASBBaseWeapon* AmmoEmptyWeapon);
	void ChangeClip();
};
