// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/BSRifleWeapon.h"

#include "Kismet/GameplayStatics.h"

void ABSRifleWeapon::StartFire()
{
	Super::StartFire();
	InitMuzzleFX();
	GetWorldTimerManager().SetTimer(ShotTimerHandle,this,&ABSBaseWeapon::MakeShot,FireRate,true);
}
void ABSRifleWeapon::StopFire()
{
	SetMuzzleFXVisible(false);
	GetWorldTimerManager().ClearTimer(ShotTimerHandle);
}
void ABSRifleWeapon::InitMuzzleFX()
{
	if(!MuzzleFXComponent)
	{
		MuzzleFXComponent = SpawnMuzzleFX();
	}
	SetMuzzleFXVisible(true);
}
void ABSRifleWeapon::SetMuzzleFXVisible(bool Visibility)
{
	if(!MuzzleFXComponent)
	{
		return;
	}
	MuzzleFXComponent->SetPaused(!Visibility);
	MuzzleFXComponent->SetVisibility(Visibility,true);
}

