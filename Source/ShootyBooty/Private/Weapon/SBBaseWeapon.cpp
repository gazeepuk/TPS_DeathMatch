// ShootyBooty by @GazeePuk. All Rights Reversed


#include "Weapon/SBBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include"GameFramework/Character.h"
#include"GameFramework/Controller.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon, All, All);

ASBBaseWeapon::ASBBaseWeapon()
{
	PrimaryActorTick.bCanEverTick = false;
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	SetRootComponent(WeaponMesh);

}

void ASBBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	check(WeaponMesh);	
}


void ASBBaseWeapon::Fire()
{
	UE_LOG(LogBaseWeapon, Error, TEXT("Fire!"));

	MakeShot();
}

void ASBBaseWeapon::MakeShot()
{
	if(!GetWorld())return;

	const auto Player = Cast<ACharacter>(GetOwner());
	if(!Player) return;

	const auto Controller = Player->GetController<APlayerController>();
	if(!Controller) return;

	FVector ViewLocation;
	FRotator ViewRotation;

	Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
	
	const FTransform SocketTransform = WeaponMesh->GetSocketTransform(MuzzleSocketName);
	const FVector TraceStart = ViewLocation;
	const FVector ShootDirecrion = ViewRotation.Vector();
	const FVector TraceEnd = TraceStart+ShootDirecrion* TraceMaxDistance;

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(Player);
	
	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility, CollisionParams);

	if(HitResult.bBlockingHit)
	{
		DrawDebugLine(GetWorld(), SocketTransform.GetLocation(), HitResult.ImpactPoint,FColor::Red, false, 3.0f, 0.0f, 3.0f);
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.0f, 24, FColor::Red, false, 5.0f);

		UE_LOG(LogBaseWeapon, Warning, TEXT("Bone: %s"),*HitResult.BoneName.ToString());
	}
	else
	{
		DrawDebugLine(GetWorld(), SocketTransform.GetLocation(), TraceEnd,FColor::Red, false, 3.0f, 0.0f, 3.0f);
	}
}

