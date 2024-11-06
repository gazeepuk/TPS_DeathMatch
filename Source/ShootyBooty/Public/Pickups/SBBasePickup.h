// ShootyBooty by @GazeePuk. All Rights Reversed

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
    
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual bool GivePickupTo(APawn* InPlayerPawn);
private:	
	virtual void Tick(float DeltaSeconds) override;
	UFUNCTION(Server,Reliable)
	void Server_OnPickupWasTaken();
	UFUNCTION(Server,Reliable)
	void Server_Respawn() const;
	UFUNCTION(Client, Reliable)
	void Client_SetVisibility(bool bVisible, bool bPropagateToChildren) const;
	UFUNCTION(NetMulticast, Reliable)
	void NetMulticast_SetVisibility(bool bVisible, bool bPropagateToChildren) const;
	void AddMovement();
};
