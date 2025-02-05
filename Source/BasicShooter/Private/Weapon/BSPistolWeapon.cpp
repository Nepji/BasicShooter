// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/BSPistolWeapon.h"
void ABSPistolWeapon::MakeShot()
{
	Super::MakeShot();
	SpawnMuzzleFX();
}