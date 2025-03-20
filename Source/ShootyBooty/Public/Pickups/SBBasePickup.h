// Developed by Ivan Piankouski
// GitHub / LinkedIn: gazeepuk

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SBBasePickup.generated.h"

class USphereComponent;

UCLASS()
class SHOOTYBOOTY_API ASBBasePickup : public AActor
{
	GENERATED_BODY()
	
public:	
	ASBBasePickup();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category="Pickups")
	USphereComponent* CollisionComponent;

    UPROPERTY(EditAnywhere, Category="Pickups")
    float RespawnTime = 5.0f;
    
	virtual bool GivePickupTo(APawn* InPlayerPawn);


private:	
	virtual void Tick(float DeltaSeconds) override;
	void OnPickupWasTaken();
	void Respawn() const;
	UFUNCTION(NetMulticast, Reliable)
	void NetMulticast_SetVisibility(bool bVisible, bool bPropagateToChildren) const;
	void AddMovement();

	UFUNCTION()
	void OnPickupCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
};
