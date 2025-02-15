// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BSCoreTypes.h"
#include "Blueprint/UserWidget.h"
#include "BSMenuLevelItemWidget.generated.h"

class UImage;
class UButton;
class UTextBlock;
/**
 *
 */
UCLASS()
class BASICSHOOTER_API UBSMenuLevelItemWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	FOnLevelSelectedSignature OnLevelSelected;

public:
	void SetLevelData(const FLevelData& Data);
	FLevelData GetLevelData() const;

	void SetSelected(bool IsSelected);
protected:
	UPROPERTY(meta = (BindWidget))
	UButton* LevelSelectButton;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* LevelNameTextBlock;
	
	UPROPERTY(meta = (BindWidget))
	UImage* LevelImage;

	UPROPERTY(meta = (BindWidget))
	UImage* FrameImage;

protected:
	virtual void NativeOnInitialized() override;

private:
	FLevelData LevelData;

private:
	UFUNCTION()
	void OnLevelItemClicked();
};
