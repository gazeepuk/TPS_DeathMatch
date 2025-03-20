// Developed by Ivan Piankouski
// GitHub / LinkedIn: gazeepuk

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SBBaseCharacter.generated.h"

class USBWeaponComponent;
class UTextRenderComponent;
class USBHealthComponent;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;

UCLASS()
class SHOOTYBOOTY_API ASBBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASBBaseCharacter(const FObjectInitializer& ObjInit);
	virtual void OnDeath();
	
protected:
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	//Health
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<USBHealthComponent> HealthComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UTextRenderComponent> HealthTextComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	TObjectPtr<UAnimMontage> DeathAnimMontage;

	UFUNCTION(NetMulticast, Reliable)
	void NetMulticast_OnDeath();
	
private:
	UFUNCTION()
	void OnHealthChanged(float Health) const;

	FTimerHandle RespawnTimerHandle;
	UPROPERTY(EditDefaultsOnly)
	float RespawnDelay = 3.f;
	UFUNCTION()
	void Respawn();

	//Land damage
protected:
	UPROPERTY(EditDefaultsOnly, Category="Damage")
	FVector2D LandedDamageVelocity = FVector2D(900.0f, 1200.0f);
	
	UPROPERTY(EditDefaultsOnly, Category="Damage")
	FVector2D LandedDamage = FVector2D(10.0f,100.0f);
private:
	UFUNCTION()
	void OnGroundLanded(const FHitResult& Hit);

	// Weapon
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Weapon")
	TObjectPtr<USBWeaponComponent> WeaponComponent;

	//Movement
protected:
	UPROPERTY(Replicated)
	bool bWantsToRun = false;

public:	
	UFUNCTION(BlueprintCallable, Category="Movement")
	bool IsRunning() const;
	bool IsMovingForward() const;

	UFUNCTION(BlueprintCallable, Category="Movement")
	float GetMoveDirection() const;

	//Animations
public:
	UFUNCTION(NetMulticast, Unreliable)
	void NetMulticast_PlayAnimMontage(UAnimMontage* AnimMontage, float PlayRate = 1.f);
};
