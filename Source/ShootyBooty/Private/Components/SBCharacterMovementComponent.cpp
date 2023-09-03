// ShootyBooty by @GazeePuk. All Rights Reversed


#include "Components/SBCharacterMovementComponent.h"

#include "SBBaseCharacter.h"

float USBCharacterMovementComponent::GetMaxSpeed() const
{
	const float MaxSpeed = Super::GetMaxSpeed();
	const ASBBaseCharacter* Player = Cast<ASBBaseCharacter>(GetPawnOwner());
	return Player && Player->IsRunning() ? MaxSpeed* RunModifire : MaxSpeed;
}
