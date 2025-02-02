// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BSProjectile.h"
#include "Weapon/BSBaseWeapon.h"
#include "BSLauncherWeapon.generated.h"

/**
 *
 */
UCLASS()
class BASICSHOOTER_API ABSLauncherWeapon : public ABSBaseWeapon
{
	GENERATED_BODY()

public:
	virtual void MakeShot() override;

protected:
	UPROPERTY(EditDefaultsOnly, Blueprintable, Category = "Weapon")
	TSubclassOf<AActor> ProjectileClass;
};
