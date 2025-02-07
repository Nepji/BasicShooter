// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BSFindEnemyService.generated.h"

/**
 * 
 */
UCLASS()
class BASICSHOOTER_API UBSFindEnemyService : public UBTService
{
	GENERATED_BODY()
public:
	UBSFindEnemyService();
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector EnemyActorKey;
	
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
