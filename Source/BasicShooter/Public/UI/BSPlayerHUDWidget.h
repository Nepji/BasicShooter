// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BSPlayerHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class BASICSHOOTER_API UBSPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = "UI")
	float GetHealthPercent() const;
};
