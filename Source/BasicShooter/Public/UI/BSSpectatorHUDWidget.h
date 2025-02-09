// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BSCoreTypes.h"
#include "Blueprint/UserWidget.h"
#include "BSSpectatorHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class BASICSHOOTER_API UBSSpectatorHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	bool GetRespawnTimeRemaining(FText& TimeRemaining);

	UFUNCTION(BlueprintCallable, Category = "UI")
	bool GetRandomTip(FText& TipText);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (RowType = "/Script/BasicShooter.TipsData"))
	FDataTableRowHandle TipsDataRowHandle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (ClampMin = 3))
	int32 TipTimeOnScreen = 3; // In seconds

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI");
	FString SourceColumnName = "TipDescription";
	
protected:
	virtual bool Initialize() override;
	FTimerHandle NextTipTimerHandle;
	int32 CurrentTipID = 0;
	TArray<FName> RowTipsNames;

private:
	void NextTip();
	
};
