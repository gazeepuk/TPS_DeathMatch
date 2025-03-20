// Developed by Ivan Piankouski
// GitHub / LinkedIn: gazeepuk


#include "AI/SBAICharacter.h"

#include "BrainComponent.h"
#include "SBAIWeaponComponent.h"
#include "AI/SBAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameModes/DeathMatchGameMode.h"

ASBAICharacter::ASBAICharacter(const FObjectInitializer& ObjInit)
: Super(ObjInit.SetDefaultSubobjectClass<USBAIWeaponComponent>("WeaponComponent"))
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = ASBAIController::StaticClass();

	bUseControllerRotationYaw = false;
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0, 200, 0);
	}
}

void ASBAICharacter::OnDeath()
{
	NetMulticast_OnDeath();
	float CleanupRate = DeathAnimMontage ? DeathAnimMontage->GetPlayLength() + 2.f : 3.f;
	
	GetWorldTimerManager().ClearTimer(CleanupTimerHandle);
	GetWorldTimerManager().SetTimer(CleanupTimerHandle, this, &ThisClass::Cleanup, CleanupRate);
}

void ASBAICharacter::Cleanup()
{
	AAIController* SBController = Cast<AAIController>(Controller);
	if(SBController && SBController->BrainComponent)
	{
		SBController->BrainComponent->Cleanup();
		SBController->Destroy();
	}
	
	Destroy();
}
