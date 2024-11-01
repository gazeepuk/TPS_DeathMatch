// ShootyBooty by @GazeePuk. All Rights Reversed

#pragma once

#include "CoreMinimal.h"
#include "SBBaseCharacter.h"
#include "SBPlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTYBOOTY_API ASBPlayerCharacter : public ASBBaseCharacter
{
	GENERATED_BODY()
public:
	ASBPlayerCharacter(const FObjectInitializer& ObjInit);
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
protected:
	virtual void BeginPlay() override;
	
	//Camera
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	// ~Input
private:

	//Mapping Context
	UPROPERTY(EditDefaultsOnly, Category = "Input|InputAction")
	TObjectPtr<UInputMappingContext> DefaultMappingContext;
	//Input actions
	UPROPERTY(EditDefaultsOnly, Category = "Input|InputAction|Movement")
	TObjectPtr<UInputAction> MoveAction;
	UPROPERTY(EditDefaultsOnly, Category = "Input|InputAction|Movement")
	TObjectPtr<UInputAction> LookAction;
	UPROPERTY(EditDefaultsOnly, Category = "Input|InputAction|Movement")
	TObjectPtr<UInputAction> JumpAction;
	UPROPERTY(EditDefaultsOnly, Category = "Input|InputAction|Movement")
	TObjectPtr<UInputAction> SprintAction;
	UPROPERTY(EditDefaultsOnly, Category = "Input|InputAction|Combat")
	TObjectPtr<UInputAction> FireAction;
	UPROPERTY(EditDefaultsOnly, Category = "Input|InputAction|Combat")
	TObjectPtr<UInputAction> TakeNextWeaponAction;
	UPROPERTY(EditDefaultsOnly, Category = "Input|InputAction|Combat")
	TObjectPtr<UInputAction> ReloadAction;
	
	//Functions called for input
	virtual void Move(const FInputActionValue& Value);
	virtual void Look(const FInputActionValue& Value);
	virtual void StartJumpInput(const FInputActionValue& Value);
	virtual void StartSprintInput(const FInputActionValue& Value);
	virtual void StopSprintInput(const FInputActionValue& Value);
	virtual void StartFireInput(const FInputActionValue& Value);
	virtual void StopFireInput(const FInputActionValue& Value);
	virtual void TakeNextWeapon(const FInputActionValue& Value);
	virtual void ReloadWeapon(const FInputActionValue& Value);
	
};


