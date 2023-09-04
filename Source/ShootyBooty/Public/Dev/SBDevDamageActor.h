// ShootyBooty by @GazeePuk. All Rights Reversed

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SBDevDamageActor.generated.h"

UCLASS()
class SHOOTYBOOTY_API ASBDevDamageActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASBDevDamageActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere)
	USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Radius = 300.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FColor SphereColor = FColor::Red;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage = 10.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool DoFullDamage = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UDamageType> DamageType;

	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
