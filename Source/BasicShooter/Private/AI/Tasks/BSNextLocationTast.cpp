// Fill out your copyright notice in the Description page of Project Settings.

#include "AIController.h"
#include "NavigationSystem.h"
#include "..\..\..\Public\AI\Tasks\UBSNextLocationTask.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"

UBSNextLocationTask::UBSNextLocationTask()
{
	NodeName = "Next Random Location";
}
EBTNodeResult::Type UBSNextLocationTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto Controller = OwnerComp.GetAIOwner();
	const auto Blackboard = OwnerComp.GetBlackboardComponent();

	if (!Controller || !Blackboard)
	{
		return EBTNodeResult::Failed;
	}

	const auto Pawn = Controller->GetPawn();
	if (!Pawn)
	{
		return EBTNodeResult::Failed;
	}

	const auto NavSys = UNavigationSystemV1::GetCurrent(Pawn);
	if (!NavSys)
	{
		return EBTNodeResult::Failed;
	}

	FNavLocation NavLocation;
	auto Location = Pawn->GetActorLocation();
	if(!SelfCentre)
	{
		const auto CentreActor = Cast<AActor>(Blackboard->GetValueAsObject(CentreActorKey.SelectedKeyName));
		if(!CentreActor)
		{
			return EBTNodeResult::Failed;
		}
		Location = CentreActor->GetActorLocation();
	}
	
	if (!NavSys->GetRandomReachablePointInRadius(Location, Radius, NavLocation))
	{
		return EBTNodeResult::Failed;
	}
	Blackboard->SetValueAsVector(AimLocationKey.SelectedKeyName, NavLocation.Location);
	return EBTNodeResult::Succeeded;
}
