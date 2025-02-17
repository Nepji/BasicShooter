// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BSPlayerHUDWidget.h"
#include "GameFramework/HUD.h"
#include "BSGameHUD.generated.h"

/**
 * 
 */
UCLASS()
class BASICSHOOTER_API ABSGameHUD : public AHUD
{
	GENERATED_BODY()
public:
	virtual void DrawHUD() override;
protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "UI")
	TSubclassOf<UUserWidget> PlayerHUDWidgetClass;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "UI")
	TSubclassOf<UUserWidget> PlayerPauseWidgetClass;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "UI")
	TSubclassOf<UUserWidget> GameOverWidgetClass;

	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TMap<EBSMatchState, UBSBaseWidget*> GameWidgets;
	
	UPROPERTY()
	UBSBaseWidget* CurrentWidget = nullptr;
private:
	void OnMatchStateChanged(EBSMatchState State);
};
