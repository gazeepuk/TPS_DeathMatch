// Developed by Ivan Piankouski
// GitHub / LinkedIn: gazeepuk


#include "Components/SBCharacterMovementComponent.h"

#include "SBBaseCharacter.h"

float USBCharacterMovementComponent::GetMaxSpeed() const
{
	const float MaxSpeed = Super::GetMaxSpeed();
	const ASBBaseCharacter* Player = Cast<ASBBaseCharacter>(GetPawnOwner());

	//Returns modified MaxSpeed if Character is running
	if(Player && Player->IsRunning())
	{
		return MaxSpeed * RunModifier;
	}
	return MaxSpeed;
}
