// Developed by Ivan Piankouski
// GitHub / LinkedIn: gazeepuk


#include "Animations/SBAnimNotify.h"

void USBAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	OnNotified.Broadcast(MeshComp);
	Super::Notify(MeshComp, Animation, EventReference);
}
