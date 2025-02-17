// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BSBaseWidget.h"
#include "BSCoreTypes.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "BSGameOverHUDWidget.generated.h"

class UVerticalBox;

/**
 *
 */
UCLASS()
class BASICSHOOTER_API UBSGameOverHUDWidget : public UBSBaseWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;

protected:
	UPROPERTY(meta = (BindWidget))
	UVerticalBox* PlayerStatBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> PlayerStatRowWidgetClass;
	
	UPROPERTY(meta = (BindWidget))
	UButton* RestartButton;

	UPROPERTY(meta = (BindWidget))
	UButton* MainMenuButton;

private:
	UFUNCTION()
	void OnRestart();
	UFUNCTION()
	void OnMainMenu();

	void OnMatchStateChanged(EBSMatchState State);
	void UpdatePlayerStat();
};
