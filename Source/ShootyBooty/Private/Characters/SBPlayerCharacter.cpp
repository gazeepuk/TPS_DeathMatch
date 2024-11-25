// ShootyBooty by @GazeePuk. All Rights Reversed


#include "SBPlayerCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "SBCharacterMovementComponent.h"
#include "SBWeaponComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

ASBPlayerCharacter::ASBPlayerCharacter(const FObjectInitializer& ObjInit):
Super(ObjInit.SetDefaultSubobjectClass<USBCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->SocketOffset = FVector(0,100.0f,80.0f);
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);
}

void ASBPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void ASBPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if(UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//Binds input actions
		if(IsValid(MoveAction))
		{
			EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Move);
		}
		if(IsValid(LookAction))
		{
			EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ThisClass::Look);
		}
		if(IsValid(JumpAction))
		{
			EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ThisClass::StartJumpInput);
		}
		if(IsValid(SprintAction))
		{
			EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &ThisClass::StartSprintInput);
			EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &ThisClass::StopSprintInput);
		}
		if(IsValid(FireAction))
		{
			EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Started, this, &ThisClass::StartFireInput);
			EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Completed, this, &ThisClass::StopFireInput);
		}
		if(IsValid(EquipNextWeaponAction))
		{
			EnhancedInputComponent->BindAction(EquipNextWeaponAction, ETriggerEvent::Started, this, &ThisClass::EquipNextWeapon);
		}
		if(IsValid(ReloadAction))
		{
			EnhancedInputComponent->BindAction(ReloadAction, ETriggerEvent::Started, this, &ThisClass::ReloadWeapon);
		}
	}
}

void ASBPlayerCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}

	bMovingForward = MovementVector.Y > 0;
}

void ASBPlayerCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ASBPlayerCharacter::StartJumpInput(const FInputActionValue& Value)
{
	Jump();
}

void ASBPlayerCharacter::StartSprintInput(const FInputActionValue& Value)
{
	bWantsToRun = true;
}

void ASBPlayerCharacter::StopSprintInput(const FInputActionValue& Value)
{
	bWantsToRun = false;
}

void ASBPlayerCharacter::StartFireInput(const FInputActionValue& Value)
{
	Server_StartFire();
}

void ASBPlayerCharacter::StopFireInput(const FInputActionValue& Value)
{
	Server_StopFire();
}

void ASBPlayerCharacter::EquipNextWeapon(const FInputActionValue& Value)
{
	Server_EquipNextWeapon();
}

void ASBPlayerCharacter::ReloadWeapon(const FInputActionValue& Value)
{
	Server_Reload();
}

void ASBPlayerCharacter::Server_EquipNextWeapon_Implementation()
{
	if(WeaponComponent)
	{
		WeaponComponent->EquipNextWeapon();
	}
}

void ASBPlayerCharacter::Server_Reload_Implementation()
{
	if(WeaponComponent)
	{
		WeaponComponent->Reload();
	}
}

void ASBPlayerCharacter::Server_StartFire_Implementation()
{
	if(WeaponComponent)
	{
		WeaponComponent->StartFire();
	}
}

void ASBPlayerCharacter::Server_StopFire_Implementation()
{
	if(WeaponComponent)
	{
		WeaponComponent->StopFire();
	}
}
