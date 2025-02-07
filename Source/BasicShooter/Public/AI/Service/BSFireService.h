// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BSFireService.generated.h"

/**
 * 
 */
UCLASS()
class BASICSHOOTER_API UBSFireService : public UBTService
{
	GENERATED_BODY()
public:
	UBSFireService();
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector EnemyActorKey;

	/** Accuracy of Directional looking */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float Threshold = 0.75f;
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
