// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BSBaseWidget.generated.h"

class USoundCue;

UCLASS()
class BASICSHOOTER_API UBSBaseWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void Show();
protected:
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* ShowAnimation;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "Sound")
	USoundCue* OpenSound;
};
