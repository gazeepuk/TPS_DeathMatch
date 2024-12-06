// ShootyBooty by @GazeePuk. All Rights Reversed

#pragma once

#include "CoreMinimal.h"
#include "SBPlayerController.h"
#include "GameFramework/GameMode.h"
#include "DeathMatchGameMode.generated.h"

class ASBPlayerController;
class ASBPlayerCharacter;

namespace MatchState
{
	extern SHOOTYBOOTY_API const FName Cooldown; // Match has ended. Display winner and begin cooldown timer
}
/**
 * 
 */
UCLASS()
class SHOOTYBOOTY_API ADeathMatchGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	ADeathMatchGameMode();

	FORCEINLINE float GetWarmupTime() const { return WarmupTime; }
	FORCEINLINE float GetMatchTime() const { return MatchTime; }
	FORCEINLINE float GetCooldownTime() const { return CooldownTime; }
	FORCEINLINE float GetLevelStartingTime() const { return LevelStartingTime; }

	virtual void PlayerEliminated(ASBPlayerCharacter* EliminatedCharacter, ASBPlayerController* VictimController, ASBPlayerController* AttackerController);
	void RespawnPlayer(ACharacter* EliminatedCharacter, AController* EliminatedController);
	
protected:
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void SwapPlayerControllers(APlayerController* OldPC, APlayerController* NewPC) override;
	virtual void Logout(AController* Exiting) override;

	virtual void BeginPlay() override;

	virtual void OnMatchStateSet() override;
	
	UPROPERTY(BlueprintReadOnly)
	TArray<APlayerController*> AllPlayerControllers;

	UPROPERTY(EditDefaultsOnly)
	float WarmupTime = 5.f;
	UPROPERTY(EditDefaultsOnly)
	float MatchTime = 10.f;
	UPROPERTY(EditDefaultsOnly)
	float CooldownTime = 10.f;
	
private:
	virtual void Tick(float DeltaSeconds) override;

	float LevelStartingTime = 0.f;
	float CountdownTime = 0.f;
};
