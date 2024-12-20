// Developed by Ivan Piankouski
// GitHub / LinkedIn: gazeepuk

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SBCharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTYBOOTY_API USBCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
public:
	virtual float GetMaxSpeed() const override;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Movement", meta=(ClampMin = "1.5", ClampMax="10"))
	float RunModifier = 2.0f;
};
