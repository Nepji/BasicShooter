// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BSCoreTypes.h"
#include "Engine/GameInstance.h"
#include "BSBaseGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class BASICSHOOTER_API UBSBaseGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void SetStartupLevel(const FLevelData& Data);
	UFUNCTION()
	FLevelData GetStartupLevel() const;
	TArray<FLevelData> GetLevelsData();
	FName GetMenuLevelName() const;

	void ToggleVolume() const;

protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "Level")
	TArray<FLevelData> LevelsData;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "Level")
	FName MenuLevelName = NAME_None;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "Sound")
	USoundClass* MasterSoundClass;


private:
	FLevelData CurrentLevel;
};
