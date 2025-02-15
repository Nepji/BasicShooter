// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BSMenuGameHUD.generated.h"

/**
 * 
 */
UCLASS()
class BASICSHOOTER_API ABSMenuGameHUD : public AHUD
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> MenuWidgetClass;
protected:
	virtual void BeginPlay() override;
};
