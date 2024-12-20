// Developed by Ivan Piankouski
// GitHub / LinkedIn: gazeepuk

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "LobbyGameState.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTYBOOTY_API ALobbyGameState : public AGameStateBase
{
	GENERATED_BODY()

	virtual void RemovePlayerState(APlayerState* PlayerState) override;
};
