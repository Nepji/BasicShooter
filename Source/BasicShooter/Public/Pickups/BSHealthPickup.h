// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/BSBasePickup.h"
#include "BSHealthPickup.generated.h"

/**
 * 
 */
UCLASS()
class BASICSHOOTER_API ABSHealthPickup : public ABSBasePickup
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Pickup", meta = (ClampMin = 0))
	int32 AmountOfHealth = 50;


protected:
	virtual bool PickUpTo(APawn* PlayerPawn) override;
	
};
