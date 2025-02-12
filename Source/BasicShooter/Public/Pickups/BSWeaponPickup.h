// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BSBasePickup.h"
#include "BSWeaponPickup.generated.h"

UCLASS()
class BASICSHOOTER_API ABSWeaponPickup : public ABSBasePickup
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Pickup")
	FWeaponData WeaponData;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Pickup")
	FAmmoData AmmoData;

protected:
	virtual bool PickUpTo(APawn* PlayerPawn) override;
};
