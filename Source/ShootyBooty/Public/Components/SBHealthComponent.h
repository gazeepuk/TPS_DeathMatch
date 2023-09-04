// ShootyBooty by @GazeePuk. All Rights Reversed

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SBHealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeath)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float)

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SHOOTYBOOTY_API USBHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	USBHealthComponent();

	float GetHealth() const { return Health; }

	UFUNCTION(BlueprintCallable)
	bool IsDead() const {return  FMath::IsNearlyZero(Health);}

	UFUNCTION(BlueprintCallable)
	void OnHealed();
	
	FOnDeath OnDeath;
	FOnHealthChanged OnHealthChanged;	
protected:
	virtual void BeginPlay() override;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin="0.0", ClampMax="1000"), Category="Health")
	float MaxHealth = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Health")
	bool bAutoHeal = true;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Health", meta=(EditCondition="bAutoHeal"))
	float HealthUpdateTime = 0.3;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Health", meta=(EditCondition="bAutoHeal"))
	float HealthDelay = 3.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Health", meta=(EditCondition="bAutoHeal"))
	float HealthModifier = 1.0f;

	FTimerHandle HealTimerHandle;
	
private:
	UFUNCTION()
	void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	AController* InstigatedBy, AActor* DamageCauser);
	float Health = 0.0f;
	void SetHealth(float NewHealth);
};
