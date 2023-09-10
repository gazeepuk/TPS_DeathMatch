// ShootyBooty by @GazeePuk. All Rights Reversed

#pragma once

#include "CoreMinimal.h"
#include "Weapon/SBBaseWeapon.h"
#include "SBRifleWeapon.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTYBOOTY_API ASBRifleWeapon : public ASBBaseWeapon
{
	GENERATED_BODY()

public:
	virtual void StartFire() override;
	virtual void StopFire() override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float TimeBetweenShots = 0.1f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	double BulletSpreed = 1.5f;

	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) override;
	virtual void MakeShot() override;

private:
	void MakeDamage(FHitResult& HitResult);
};
