// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BSWeaponComponent.h"
#include "BSAIWeaponComponent.generated.h"

/**
 * 
 */
UCLASS()
class BASICSHOOTER_API UBSAIWeaponComponent : public UBSWeaponComponent
{
	GENERATED_BODY()

public:
	virtual void StartFire() override;
	virtual void StopFire() override;
	void NextLoadWeapon();
	
	
};
