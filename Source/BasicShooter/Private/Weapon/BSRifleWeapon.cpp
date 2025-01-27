// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/BSRifleWeapon.h"

#include "Kismet/GameplayStatics.h"

void ABSRifleWeapon::StartFire()
{
	MakeShot();
	GetWorldTimerManager().SetTimer(ShotTimerHandle,this,&ABSBaseWeapon::MakeShot,FireRate,true);
}
void ABSRifleWeapon::StopFire()
{
	GetWorldTimerManager().ClearTimer(ShotTimerHandle);
}

