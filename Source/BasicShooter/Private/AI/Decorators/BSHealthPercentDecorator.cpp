// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/Decorators/BSHealthPercentDecorator.h"

#include "BSCoreUtils.h"
#include "Components/BSHealthComponent.h"
UBSHealthPercentDecorator::UBSHealthPercentDecorator()
{
	NodeName = "Health Percent";
}
bool UBSHealthPercentDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const auto Controller = OwnerComp.GetOwner();
	if(!Controller)
	{
		return false;
	}

	const auto HealthComponent = BSCoreUtils::GetActorComponent<UBSHealthComponent>(Controller);
	if(!HealthComponent || HealthComponent->IsDead())
	{
		return false;
	}
	
	return HealthComponent->GetHealth() <= HealthPercent;
}