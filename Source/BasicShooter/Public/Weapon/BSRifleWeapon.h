// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/BSBaseWeapon.h"
#include "BSRifleWeapon.generated.h"


class UNiagaraComponent;

UCLASS()
class BASICSHOOTER_API ABSRifleWeapon : public ABSBaseWeapon
{
	GENERATED_BODY()
public:
	virtual void StartFire() override;
	virtual void StopFire() override;
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = 0))
	float FireRate = 0.1f;

protected:
	virtual void DecreaseAmmo() override;

private:
	FTimerHandle ShotTimerHandle;

	UPROPERTY()
	UNiagaraComponent* MuzzleFXComponent;
private:
	void InitMuzzleFX();
	void SetMuzzleFXVisible(bool Visibility);
};
