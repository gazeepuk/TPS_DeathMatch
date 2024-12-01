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
	virtual void AddPlayerState(APlayerState* PlayerState) override;
	virtual void RemovePlayerState(APlayerState* PlayerState) override;

	void UpdateTopScore();

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(Replicated)
	TArray<ADeathMatchPlayerState*> TopScoringPlayerStates;
};
