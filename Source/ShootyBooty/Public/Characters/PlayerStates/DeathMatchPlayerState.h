// ShootyBooty by @GazeePuk. All Rights Reversed

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "DeathMatchPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTYBOOTY_API ADeathMatchPlayerState : public APlayerState
{
	GENERATED_BODY()
public:
	void AddScore();
};
