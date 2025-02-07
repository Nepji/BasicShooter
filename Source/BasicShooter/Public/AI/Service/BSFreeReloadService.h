// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "Components/BSWeaponComponent.h"
#include "BSFreeReloadService.generated.h"

/**
 * 
 */
UCLASS()
class BASICSHOOTER_API UBSFreeReloadService : public UBTService
{
	GENERATED_BODY()

public:
	UBSFreeReloadService();
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
