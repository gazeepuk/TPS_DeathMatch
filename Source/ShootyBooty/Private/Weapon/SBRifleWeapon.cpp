// Developed by Ivan Piankouski
// GitHub / LinkedIn: gazeepuk


#include "Weapon/SBRifleWeapon.h"
#include"Engine/DamageEvents.h"

ASBRifleWeapon::ASBRifleWeapon()
{
	TraceMaxDistance = 50000.f;
}

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

	if (!GetPlayerViewPoint(ViewLocation, ViewRotation))
	{
		return false;
	}

	TraceStart = ViewLocation;
	float HalfRad = FMath::DegreesToRadians(BulletSpreed);
	const FVector ShootDirection = FMath::VRandCone(ViewRotation.Vector(), HalfRad);
	TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
	return true;
}

void ASBRifleWeapon::Server_MakeShot_Implementation()
{
	Super::Server_MakeShot_Implementation();
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
		Server_MakeDamage(HitResult);

		DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), HitResult.ImpactPoint, FColor::Red, false, 3.0f, 0.0f,
		              3.0f);
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.0f, 24, FColor::Red, false, 5.0f);
	}
	else
	{
		DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), TraceEnd, FColor::Red, false, 3.0f, 0.0f, 3.0f);
	}
}

void ASBRifleWeapon::Server_MakeDamage_Implementation(const FHitResult& HitResult)
{
	MakeDamage(HitResult);
}

void ASBRifleWeapon::MakeDamage(const FHitResult& HitResult)
{
	AActor* DamagedActor = HitResult.GetActor();
	if (!DamagedActor) return;

	DamagedActor->TakeDamage(DamageAmount, FDamageEvent{}, GetPlayerController(), this);
}
