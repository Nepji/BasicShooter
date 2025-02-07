// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/Service/BSFreeReloadService.h"

#include "BSCoreUtils.h"
#include "AI/BSAIController.h"
#include "Components/BSWeaponComponent.h"


UBSFreeReloadService::UBSFreeReloadService()
{
	NodeName = "Free To Reload";
}
void UBSFreeReloadService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Controller = Cast<ABSAIController>(OwnerComp.GetAIOwner());
	if(!Controller)
	{
		Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
		return;
	}
	const auto WeaponComponent = BSCoreUtils::GetActorComponent<UBSWeaponComponent>(Controller->GetPawn());
	if (!WeaponComponent)
	{
		Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
		return;
	}

	if (WeaponComponent->IsWeaponsNeedToReload() && WeaponComponent->CanFire())
	{
		WeaponComponent->CanReload() ? WeaponComponent->Reload() : WeaponComponent->NextWeapon();
	}
}