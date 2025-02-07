// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/BSAmmoPickup.h"

#include "BSCoreUtils.h"
#include "Components/BSHealthComponent.h"
#include "Components/BSWeaponComponent.h"

bool ABSAmmoPickup::PickUpTo(APawn* PlayerPawn)
{
	const auto HealthComponent = BSCoreUtils::GetActorComponent<UBSHealthComponent>(PlayerPawn);
	if(!HealthComponent || HealthComponent->IsDead())
	{
		return false;
	}
	const auto WeaponComponent = BSCoreUtils::GetActorComponent<UBSWeaponComponent>(PlayerPawn);
	if(!WeaponComponent)
	{
		return false;
	}
	
	return WeaponComponent->TryToAddAmmo(AmountOfAmmo, UniversalAmmo ? nullptr : WeaponType);
}