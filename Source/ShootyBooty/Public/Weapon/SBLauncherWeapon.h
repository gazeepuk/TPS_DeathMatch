// Developed by Ivan Piankouski
// GitHub / LinkedIn: gazeepuk

#pragma once

#include "CoreMinimal.h"
#include "Weapon/SBBaseWeapon.h"
#include "SBLauncherWeapon.generated.h"

class ASBProjectile;
/**
 * 
 */
UCLASS()
class SHOOTYBOOTY_API ASBLauncherWeapon : public ASBBaseWeapon
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Weapon")
	TSubclassOf<ASBProjectile> ProjectileClass;

	virtual void MakeShot() override;

	void SpawnProjectile(TSubclassOf<ASBProjectile> InProjectileClass, const FTransform& InSpawnTransform, const FVector& InDirection);
};
