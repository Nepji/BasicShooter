// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/BSBasePickup.h"
#include "BSAmmoPickup.generated.h"

class ABSBaseWeapon;
/**
 *
 */
UCLASS()
class BASICSHOOTER_API ABSAmmoPickup : public ABSBasePickup
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Pickup", meta = (ClampMin = 0))
	int32 AmountOfAmmo = 90;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Pickup", meta = (EditCondition = "!UniversalAmmo"))
	TSubclassOf<ABSBaseWeapon> WeaponType;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Pickup")
	bool UniversalAmmo = true;

protected:
	virtual bool PickUpTo(APawn* PlayerPawn) override;
	
};
