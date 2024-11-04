// ShootyBooty by @GazeePuk. All Rights Reversed


#include "Weapon/SBLauncherWeapon.h"
#include "Weapon/SBProjectile.h"

void ASBLauncherWeapon::Server_MakeShot_Implementation()
{
	
	Super::Server_MakeShot_Implementation();
	
	if (!GetWorld() || IsAmmoEmpty())return;
	
	FVector TraceStart, TraceEnd;
	if (!GetTraceData(TraceStart, TraceEnd)) return;

	FHitResult HitResult;
	MakeHit(HitResult, TraceStart, TraceEnd);

	const FVector EndPoint = HitResult.bBlockingHit ? HitResult.ImpactPoint : TraceEnd;
	const FVector Direction = (EndPoint - GetMuzzleWorldLocation()).GetSafeNormal();
	
	const FTransform SpawnTransform(FRotator::ZeroRotator,GetMuzzleWorldLocation());
	NetMulticast_SpawnProjectile(ProjectileClass, SpawnTransform, Direction);
}

void ASBLauncherWeapon::NetMulticast_SpawnProjectile_Implementation(TSubclassOf<ASBProjectile> InProjectileClass,
	const FTransform& InSpawnTransform, const FVector& InDirection)
{
	ASBProjectile* Projectile = GetWorld()->SpawnActorDeferred<ASBProjectile>(ProjectileClass, InSpawnTransform);
	if(Projectile)
	{
		Projectile->SetShotDirection(InDirection);
		Projectile->SetOwner(GetOwner());
		Projectile->FinishSpawning(InSpawnTransform);
	}
}

