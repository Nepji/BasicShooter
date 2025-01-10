// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BSMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class BASICSHOOTER_API UBSMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
	float GetMaxSpeed() const override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category = "Speed Settings", meta = (ClampMin = "1.0"))
	float RunModifier = 1.0f; 
	
};
