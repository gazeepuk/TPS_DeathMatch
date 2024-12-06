// ShootyBooty by @GazeePuk. All Rights Reversed

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "DeathMatchPlayerState.generated.h"

class ADeathMatchGameState;
class ASBPlayerController;
/**
 * 
 */
UCLASS(BlueprintType)
class SHOOTYBOOTY_API ADeathMatchPlayerState : public APlayerState
{
	GENERATED_BODY()
public:
	ADeathMatchPlayerState();

	void AddScore(const float AdditiveValue);
	void AddDefeats(const float AdditiveValue) {Defeats += AdditiveValue;}

	UFUNCTION(BlueprintCallable, BlueprintPure)
	int32 GetDefeats() const { return Defeats; }


private:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	TObjectPtr<ASBPlayerController> SBPlayerController;
	TObjectPtr<ADeathMatchGameState> DeathMatchGameState;

	void OnScoreSet();
	virtual void OnRep_Score() override;

	UPROPERTY(Replicated)
	int32 Defeats = 0.f;
};
