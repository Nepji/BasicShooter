// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Service/BSFindEnemyService.h"

#include "AIController.h"
#include "BSCoreUtils.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/BSAIPerceptionComponent.h"

UBSFindEnemyService::UBSFindEnemyService()
{
	NodeName = "Find Enemy";
}
void UBSFindEnemyService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	if(const auto BlackBoard = OwnerComp.GetBlackboardComponent())
	{
		const auto AIController = OwnerComp.GetAIOwner();
		if(const auto PerceptionComponent = BSCoreUtils::GetActorComponent<UBSAIPerceptionComponent>(AIController))
		{
			BlackBoard->SetValueAsObject(EnemyActorKey.SelectedKeyName,PerceptionComponent->GetClosestEnemy());
		}
	}
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}