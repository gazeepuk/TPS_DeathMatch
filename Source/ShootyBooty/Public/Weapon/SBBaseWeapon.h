// ShootyBooty by @GazeePuk. All Rights Reversed

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SBBaseWeapon.generated.h"

class USkeletalMeshComponent;

UCLASS()
class SHOOTYBOOTY_API ASBBaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	ASBBaseWeapon();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* WeaponMesh;
	
public:	

};
