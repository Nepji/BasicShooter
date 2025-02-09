// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BSBaseCharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BSAICharacter.generated.h"

/**
 * 
 */
UCLASS()
class BASICSHOOTER_API ABSAICharacter : public ABSBaseCharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="AI")
	UBehaviorTree* BehaviorTreeAsset;
	
public:
	ABSAICharacter(const FObjectInitializer& OnjInit);

protected:
	virtual void OnDeath() override;
	
};
