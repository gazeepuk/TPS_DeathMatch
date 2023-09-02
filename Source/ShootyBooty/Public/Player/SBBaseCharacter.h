// ShootyBooty by @GazeePuk. All Rights Reversed

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SBBaseCharacter.generated.h"

class UCameraComponent;

UCLASS()
class SHOOTYBOOTY_API ASBBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASBBaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UCameraComponent* CameraComponent;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
