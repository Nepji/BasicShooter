// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/BSBaseWeapon.h"
#include "BSPistolWeapon.generated.h"

/**
 * 
 */
UCLASS()
class BASICSHOOTER_API ABSPistolWeapon : public ABSBaseWeapon
{
	GENERATED_BODY()
public:
	virtual void MakeShot() override;
};
