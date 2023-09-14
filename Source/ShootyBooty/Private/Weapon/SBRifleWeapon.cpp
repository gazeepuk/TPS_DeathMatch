// ShootyBooty by @GazeePuk. All Rights Reversed


#include "Weapon/SBRifleWeapon.h"
#include"Engine/DamageEvents.h"

void ASBRifleWeapon::StartFire()
{
	GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &ASBBaseWeapon::StartFire, TimeBetweenShots, true);
	Super::StartFire();
}

void ASBRifleWeapon::StopFire()
{
	Super::StopFire();
	GetWorldTimerManager().ClearTimer(ShotTimerHandle);
}

bool ASBRifleWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd)
{
	FVector ViewLocation;
	FRotator ViewRotation;

	if (!GetPlayerViewPoint(ViewLocation, ViewRotation)) return false;

	TraceStart = ViewLocation;
	float HalfRad = FMath::DegreesToRadians(BulletSpreed);
	const FVector ShootDirecrion = FMath::VRandCone(ViewRotation.Vector(), HalfRad);
	TraceEnd = TraceStart + ShootDirecrion * TraceMaxDistance;
	return true;
}

void ASBRifleWeapon::MakeShot()
{
	Super::MakeShot();
	if (!GetWorld() || IsAmmoEmpty())
	{
		StopFire();
		return;
	}

	FVector TraceStart, TraceEnd;
	if (!GetTraceData(TraceStart, TraceEnd))
	{
		StopFire();
		return;
	}

	FHitResult HitResult;
	MakeHit(HitResult, TraceStart, TraceEnd);

	if (HitResult.bBlockingHit)
	{
		MakeDamage(HitResult);

		DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), HitResult.ImpactPoint, FColor::Red, false, 3.0f, 0.0f,
		              3.0f);
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.0f, 24, FColor::Red, false, 5.0f);
	}
	else
	{
		DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), TraceEnd, FColor::Red, false, 3.0f, 0.0f, 3.0f);
	}
}

void ASBRifleWeapon::MakeDamage(FHitResult& HitResult)
{
	const auto DamagedActor = HitResult.GetActor();
	if (!DamagedActor) return;

	DamagedActor->TakeDamage(DamageAmount, FDamageEvent{}, GetPlayerController(), this);
}
