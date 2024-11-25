// ShootyBooty by @GazeePuk. All Rights Reversed

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "DeathMatchGameMode.generated.h"


/**
 * 
 */
UCLASS()
class SHOOTYBOOTY_API ADeathMatchGameMode : public AGameMode
{
	GENERATED_BODY()
public:
	ADeathMatchGameMode();

	UPROPERTY(EditDefaultsOnly)
	float WarmupTime = 5.f;

	float LevelStartingTime = 0.f;
protected:
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void SwapPlayerControllers(APlayerController* OldPC, APlayerController* NewPC) override;
	virtual void Logout(AController* Exiting) override;

	virtual void BeginPlay() override;

	virtual void OnMatchStateSet() override;
	
	UPROPERTY(BlueprintReadOnly)
	TArray<APlayerController*> AllPlayerControllers;

private:
	virtual void Tick(float DeltaSeconds) override;
	
	float CountdownTime = 0.f;
};
