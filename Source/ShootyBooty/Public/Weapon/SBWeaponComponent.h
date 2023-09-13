// ShootyBooty by @GazeePuk. All Rights Reversed

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SBWeaponComponent.generated.h"

class ASBBaseWeapon;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTYBOOTY_API USBWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USBWeaponComponent();

	void StartFire();
	void StopFire();
	void NextWeapon();
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	TArray<TSubclassOf<ASBBaseWeapon>> WeaponClasses;

	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	FName WeaponEquipSocketName = "WeaponSocket";

	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	FName WeaponArmorySocketName = "ArmorySocket"; 
	
private:

	UPROPERTY()
	ASBBaseWeapon* CurrentWeapon;

	UPROPERTY()
	TArray<ASBBaseWeapon*> Weapons;

	int32 CurrentWeaponIndex = 0;
	
	void SpawnWeapons();
	void AttachWeaponToSocket(ASBBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName);
	void EquipWeapon(int32 WeaponIndex);
};
