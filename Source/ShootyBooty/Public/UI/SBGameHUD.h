// ShootyBooty by @GazeePuk. All Rights Reversed

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SBGameHUD.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTYBOOTY_API ASBGameHUD : public AHUD
{
	GENERATED_BODY()
public:
	virtual void DrawHUD() override;

private:
	void DrawCrossHair();
};
