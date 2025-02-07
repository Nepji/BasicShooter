// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "EnvQueryTest_PickUpCouldBeTaken.generated.h"

/**
 * 
 */
UCLASS()
class BASICSHOOTER_API UEnvQueryTest_PickUpCouldBeTaken : public UEnvQueryTest
{
	GENERATED_BODY()
public:
	UEnvQueryTest_PickUpCouldBeTaken(const FObjectInitializer& ObjInit);

protected:
	virtual void RunTest(FEnvQueryInstance& QueryInstance) const override;
};
