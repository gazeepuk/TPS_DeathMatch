// ShootyBooty by @GazeePuk. All Rights Reversed

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "DeathMatchGameState.generated.h"

class ADeathMatchPlayerState;
/**
 * 
 */
UCLASS(BlueprintType)
class SHOOTYBOOTY_API ADeathMatchGameState : public AGameState
{
	GENERATED_BODY()

public:
	ADeathMatchGameState();
	TArray<APlayerState*> GetTopScoringPlayers() const;
};
