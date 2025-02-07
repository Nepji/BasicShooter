// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Components/BSAIPerceptionComponent.h"
#include "BSAIController.generated.h"

/**
 * 
 */
UCLASS()
class BASICSHOOTER_API ABSAIController : public AAIController
{
	GENERATED_BODY()

public:
	ABSAIController();
	
	bool IsLookTowardsEnemy(const float Threshold) const;
	
protected:
	UPROPERTY(VisibleAnywhere,Blueprintable,Category = "Components")
	UBSAIPerceptionComponent* AIPerceptionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FName FocusOnKeyName = "EnemyActor";
protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaSeconds) override;

private:
	AActor* GetFocusedOnActor() const;

};
