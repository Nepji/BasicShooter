// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BSBaseWidget.h"
#include "Blueprint/UserWidget.h"
#include "BSPauseHUDWidget.generated.h"

class UButton;
/**
 *
 */
UCLASS()
class BASICSHOOTER_API UBSPauseWidget : public UBSBaseWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;

protected:
	UPROPERTY(meta = (BindWidget))
	UButton* ClearPauseButton;

	UPROPERTY(meta = (BindWidget))
	UButton* MainMenuButton;

private:
	UFUNCTION()
	void OnClearPause();
	UFUNCTION()
	void OnMainMenu();
};
