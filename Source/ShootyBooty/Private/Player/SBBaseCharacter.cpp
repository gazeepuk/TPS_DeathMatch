// ShootyBooty by @GazeePuk. All Rights Reversed


#include "Player/SBBaseCharacter.h"
// Sets default values
ASBBaseCharacter::ASBBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}
// Called when the game starts or when spawned
void ASBBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASBBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASBBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

