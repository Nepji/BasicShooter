// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/AI/BSAIWeaponComponent.h"

void UBSAIWeaponComponent::StartFire()
{
	if (!CanFire())
	{
		return;
	}
	CurrentWeapon->IsClipEmpty() ? NextLoadWeapon() : CurrentWeapon->StartFire();
}
void UBSAIWeaponComponent::StopFire()
{
	Super::StopFire();
}
void UBSAIWeaponComponent::NextLoadWeapon()
{
	int32 NextIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
	while(NextIndex != CurrentWeaponIndex)
	{
		if(!Weapons[NextIndex]->IsClipEmpty())
		{
			break;
		}
		NextIndex = (NextIndex + 1) % Weapons.Num();
	}
	if(CurrentWeaponIndex != NextIndex)
	{
		CurrentWeaponIndex = NextIndex;
		EquipWeapon(CurrentWeaponIndex);
	}
}