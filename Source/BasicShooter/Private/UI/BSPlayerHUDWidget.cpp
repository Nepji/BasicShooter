// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BSPlayerHUDWidget.h"

#include "Components/BSHealthComponent.h"
#include "Components/BSWeaponComponent.h"
#include "Kismet/GameplayStatics.h"
#include "BSCoreUtils.h"

float UBSPlayerHUDWidget::GetHealthPercent()
{
	if (const auto HealthComponent = BSCoreUtils::GetActorComponent<UBSHealthComponent>(GetOwningPlayerPawn()))
	{
		return HealthComponent->GetHealthPercent();
	}
	return 0.0f;
}
FString UBSPlayerHUDWidget::GetAmmoDataText()
{
	FAmmoData AmmoData;
	GetWeaponAmmoData(AmmoData);
	const FString FullCapacityLabel = AmmoData.Infinite?"∞":FString::FromInt(AmmoData.BulletAmount);
	const FString BulletsInClip = FString::FromInt(AmmoData.BulletsInClip);
	return FString::Printf(TEXT("%s  /  %s"),*BulletsInClip,*FullCapacityLabel);
		
}
bool UBSPlayerHUDWidget::GetWeaponUIData(FWeaponUIData& UIData)
{
	if (const auto WeaponComponent = BSCoreUtils::GetActorComponent<UBSWeaponComponent>(GetOwningPlayerPawn()))
	{
		return WeaponComponent->GetWeaponUIData(UIData);
	}
	return false;
}
bool UBSPlayerHUDWidget::GetWeaponAmmoData(FAmmoData& AmmoData)
{
	if (const auto WeaponComponent = BSCoreUtils::GetActorComponent<UBSWeaponComponent>(GetOwningPlayerPawn()))
	{
		return WeaponComponent->GetWeaponAmmoData(AmmoData);
	}
	return false;
}
bool UBSPlayerHUDWidget::IsPlayerAlive() const
{
	if (const auto HealthComponent = BSCoreUtils::GetActorComponent<UBSHealthComponent>(GetOwningPlayerPawn()))
	{
		return !HealthComponent->IsDead();
	}
	return false;
}
bool UBSPlayerHUDWidget::IsPlayerSpectating() const
{
	if (const auto Controller = GetOwningPlayer())
	{
		return Controller->GetStateName() == NAME_Spectating;
	}
	return false;
}
bool UBSPlayerHUDWidget::Initialize()
{
	if (const auto HealthComponent = BSCoreUtils::GetActorComponent<UBSHealthComponent>(GetOwningPlayerPawn()))
	{
		HealthComponent->OnHealthChange.AddUObject(this, &UBSPlayerHUDWidget::OnHealthChange);
	}
	return Super::Initialize();
}
void UBSPlayerHUDWidget::OnHealthChange(float Health, float HealthDelta)
{
	if(HealthDelta > 0.0f)
	{
		OnTakeDamage();
	}
	
}