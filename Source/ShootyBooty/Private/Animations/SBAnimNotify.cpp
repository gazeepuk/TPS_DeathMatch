// ShootyBooty by @GazeePuk. All Rights Reversed


#include "Animations/SBAnimNotify.h"

void USBAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	OnNotified.Broadcast(MeshComp);
	Super::Notify(MeshComp, Animation);
}
