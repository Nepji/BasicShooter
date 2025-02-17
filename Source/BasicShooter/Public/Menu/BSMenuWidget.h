// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BSCoreTypes.h"

#include "Blueprint/UserWidget.h"
#include "UI/BSBaseWidget.h"
#include "BSMenuWidget.generated.h"

class UBSBaseGameInstance;
class UHorizontalBox;
class UBSMenuLevelItemWidget;
class UButton;
/**
 *
 */
UCLASS()
class BASICSHOOTER_API UBSMenuWidget : public UBSBaseWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(meta = (BindWidget))
	UButton* StartGameButton;

	UPROPERTY(meta = (BindWidget))
	UButton* QuitGameButton;
	
	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* LevelItemBox;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* HideAnimation;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "UI")
	TSubclassOf<UUserWidget> LevelItemWidgetClass;
protected:
	virtual void NativeOnInitialized() override;
	virtual void OnAnimationFinished_Implementation(const UWidgetAnimation* Animation) override;

private:
	UPROPERTY()
	TArray<UBSMenuLevelItemWidget*> LevelItemWidgets;
private:
	UFUNCTION()
	void OnStartGame();
	
	UFUNCTION()
	void OnQuitGame();

	void InitLevelItems();
	void OnLevelSelected(const FLevelData& Data);
	UBSBaseGameInstance* GetBaseGameInstance() const;
};
