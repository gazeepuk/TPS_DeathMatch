// Developed by Ivan Piankouski
// GitHub / LinkedIn: gazeepuk


#include "AI/SBAICharacter.h"

#include "BrainComponent.h"
#include "SBAIWeaponComponent.h"
#include "AI/SBAIController.h"
#include "GameFramework/CharacterMovementComponent.h"

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
	Super::OnDeath();

	const auto SBController =  Cast<AAIController>(Controller);
	if(SBController && SBController->BrainComponent)
	{
		SBController->BrainComponent->Cleanup();
	}
}
