// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/Service/BSFireService.h"

#include "AIController.h"
#include "BSCoreUtils.h"
#include "AI/BSAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/BSWeaponComponent.h"

UBSFireService::UBSFireService()
{
	NodeName = "Fire";
}
void UBSFireService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Controller = Cast<ABSAIController>(OwnerComp.GetAIOwner());
	const auto BlackBoard = OwnerComp.GetBlackboardComponent();

	if (Controller || BlackBoard)
	{
		const auto HasAim = BlackBoard->GetValueAsObject(EnemyActorKey.SelectedKeyName);
		const auto WeaponComponent = BSCoreUtils::GetActorComponent<UBSWeaponComponent>(Controller->GetPawn());
		if (WeaponComponent)
		{
			HasAim && Controller->IsLookTowardsEnemy(Threshold) ? WeaponComponent->StartFire() : WeaponComponent->StopFire();
		}
	}
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}