// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/Decorators/BSAmmoLoadPercentDecorator.h"

#include "BSCoreUtils.h"
#include "Components/BSHealthComponent.h"
#include "Components/BSWeaponComponent.h"

class UBSHealthComponent;
UBSAmmoLoadPercentDecorator::UBSAmmoLoadPercentDecorator()
{
	NodeName = "Ammo Load Percent";
}
bool UBSAmmoLoadPercentDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const auto Controller = OwnerComp.GetOwner();
	if(!Controller)
	{
		return false;
	}

	const auto HealthComponent = BSCoreUtils::GetActorComponent<UBSHealthComponent>(Controller);
	const auto WeaponComponent = BSCoreUtils::GetActorComponent<UBSWeaponComponent>(Controller);
	if(!HealthComponent || HealthComponent->IsDead() || !WeaponComponent)
	{
		return false;
	}
	
	return WeaponComponent->GetCurrentAmmoLoadPercent() <= AmmoLoadPercent;
}