// ShootyBooty by @GazeePuk. All Rights Reversed

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SBBaseWeapon.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnClipEmptySignature, ASBBaseWeapon* BaseWeapon);

class USkeletalMeshComponent;

USTRUCT(BlueprintType)
struct FAmmoData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
	int32 Bullets;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon", meta=(EditCondition="!bInfinite"))
	int32 Clips;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
	bool bInfinite;
};

USTRUCT(BlueprintType)
struct FWeaponUIData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="UI")
	UTexture2D* MainIcon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="UI")
	UTexture2D* CrossHairIcon;
	
};

UCLASS(Abstract)
class SHOOTYBOOTY_API ASBBaseWeapon : public AActor
{
	GENERATED_BODY()

public:
	ASBBaseWeapon();

	FOnClipEmptySignature OnClipEmpty;

	virtual void StartFire();
	virtual void StopFire();
	void ChangeClip();
	bool CanReload() const;

	FWeaponUIData GetUIData() const {return UIData;}
	FAmmoData GetAmmoData() const {return CurrentAmmo;}

	bool TryToAddAmmo(int32 InClipsAmount);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
	FName MuzzleSocketName = "MuzzleSocket";

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
	float TraceMaxDistance = 1500.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
	float DamageAmount = 10.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
	FAmmoData DefaultAmmo{15, 10, false};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="UI")
	FWeaponUIData UIData;
	
	virtual void MakeShot();

	APlayerController* GetPlayerController() const;

	bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;

	FVector GetMuzzleWorldLocation() const;

	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd);

	void MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd);

	FTimerHandle ShotTimerHandle;

	void DecreaseAmmo();
	bool IsAmmoEmpty() const;
	bool IsClipEmpty() const;
	bool IsAmmoFull() const;
	void LogAmmo();

private:
	FAmmoData CurrentAmmo;
};
