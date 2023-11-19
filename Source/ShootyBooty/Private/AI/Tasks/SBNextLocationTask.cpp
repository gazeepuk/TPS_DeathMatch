// ShootyBooty by @GazeePuk. All Rights Reversed


#include "AI/Tasks/SBNextLocationTask.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

USBNextLocationTask::USBNextLocationTask()
{
	NodeName = "Next Location";
}

EBTNodeResult::Type USBNextLocationTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto Controller = OwnerComp.GetAIOwner();
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	if(!Controller || !Blackboard)
	{
		return EBTNodeResult::Failed;
	}

	const auto Pawn = Controller->GetPawn();
	if(!Pawn)
	{
		return EBTNodeResult::Failed;
	}

	const auto NavSys = UNavigationSystemV1::GetCurrent(Pawn);
	if(!NavSys)
	{
		return EBTNodeResult::Failed;
	}

	FNavLocation NavLocation;
	auto Location = Pawn->GetActorLocation();
	if(!bSelfCenter)
	{
		auto CenterActor = Cast<AActor>(Blackboard->GetValueAsObject(CenterActorKey.SelectedKeyName));
		if(!CenterActor) return EBTNodeResult::Failed;
		Location = CenterActor->GetActorLocation();
	}
	const bool bFound = NavSys->GetRandomReachablePointInRadius(Location, Radius, NavLocation);
	if(!bFound)
	{
		return EBTNodeResult::Failed;
	}

	Blackboard->SetValueAsVector(AimLocationKey.SelectedKeyName, NavLocation.Location);
	return EBTNodeResult::Succeeded;
}
