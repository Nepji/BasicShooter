// Fill out your copyright notice in the Description page of Project Settings.

#include "..\..\Public\Pickups\BSWeaponPickup.h"

#include "BSCoreUtils.h"
#include "Components/BSWeaponComponent.h"

bool ABSWeaponPickup::PickUpTo(APawn* PlayerPawn)
{
	const auto PickupResult = Super::PickUpTo(PlayerPawn);
	if(!PickupResult)
	{
		return false;
	}
	const auto WeaponComponent = BSCoreUtils::GetActorComponent<UBSWeaponComponent>(PlayerPawn);
	if(!WeaponComponent)
	{
		return false;
	}
	return WeaponComponent->TryPickupWeapon(WeaponData);
}