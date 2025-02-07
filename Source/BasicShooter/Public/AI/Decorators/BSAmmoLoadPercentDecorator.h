// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BSAmmoLoadPercentDecorator.generated.h"

/**
 *
 */
UCLASS()
class BASICSHOOTER_API UBSAmmoLoadPercentDecorator : public UBTDecorator
{
	GENERATED_BODY()
public:
	UBSAmmoLoadPercentDecorator();
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float AmmoLoadPercent =  0.6f;
	
protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
