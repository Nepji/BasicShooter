// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/BSHealthPickup.h"

#include "BSCoreUtils.h"
#include "Components/BSHealthComponent.h"

bool ABSHealthPickup::PickUpTo(APawn* PlayerPawn)
{
	const auto PickupResult = Super::PickUpTo(PlayerPawn);
	if(!PickupResult)
	{
		return false;
	}
	const auto HealthComponent = BSCoreUtils::GetActorComponent<UBSHealthComponent>(PlayerPawn);
	if(!HealthComponent || HealthComponent->IsDead())
	{
		return false;
	}
	return HealthComponent->TryAddHealth(AmountOfHealth);
}