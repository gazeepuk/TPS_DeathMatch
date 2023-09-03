// ShootyBooty by @GazeePuk. All Rights Reversed

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SBHealthComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SHOOTYBOOTY_API USBHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	USBHealthComponent();

	float GetHealth() const { return Health; }

	UFUNCTION()
	void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	AController* InstigatedBy, AActor* DamageCauser);

protected:
	virtual void BeginPlay() override;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin="0.0", ClampMax="1000"), Category="Health")
	float MaxHealth = 100.0f;

private:
	float Health = 0.0f;
};
