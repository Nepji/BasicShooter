// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/BSBaseWeapon.h"
#include "BSRifleWeapon.generated.h"

/**
 *
 */
UCLASS()
class BASICSHOOTER_API ABSRifleWeapon : public ABSBaseWeapon
{
	GENERATED_BODY()
public:
	virtual void StartFire() override;
	virtual void StopFire() override;
	virtual void MakeShot() override;
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = 0))
	float FireRate = 0.1f;
	
private:
	FTimerHandle ShotTimerHandle;
};
