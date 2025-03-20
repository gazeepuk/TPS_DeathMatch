// Developed by Ivan Piankouski
// GitHub / LinkedIn: gazeepuk


#include "Weapon/SBLauncherWeapon.h"
#include "Weapon/SBProjectile.h"

void ASBLauncherWeapon::MakeShot()
{
	
	Super::MakeShot();
	
	if (!GetWorld() || IsAmmoEmpty())return;
	
	FVector TraceStart, TraceEnd;
	if (!GetTraceData(TraceStart, TraceEnd)) return;

	FHitResult HitResult;
	MakeHit(HitResult, TraceStart, TraceEnd);

	const FVector EndPoint = HitResult.bBlockingHit ? HitResult.ImpactPoint : TraceEnd;
	const FVector Direction = (EndPoint - GetMuzzleWorldLocation()).GetSafeNormal();
	
	const FTransform SpawnTransform(FRotator::ZeroRotator,GetMuzzleWorldLocation());
	SpawnProjectile(ProjectileClass, SpawnTransform, Direction);
}

void ASBLauncherWeapon::SpawnProjectile(TSubclassOf<ASBProjectile> InProjectileClass,
	const FTransform& InSpawnTransform, const FVector& InDirection)
{
	ASBProjectile* Projectile = GetWorld()->SpawnActorDeferred<ASBProjectile>(ProjectileClass, InSpawnTransform);
	if(Projectile)
	{
		Projectile->SetShotDirection(InDirection);
		Projectile->SetOwner(GetOwner());
		Projectile->SetInstigator(GetOwner<APawn>());
		Projectile->FinishSpawning(InSpawnTransform);
	}
}
