// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BSPlayerHUDWidget.generated.h"

struct FWeaponUIData;
struct FAmmoData;
/**
 *
 */
UCLASS()
class BASICSHOOTER_API UBSPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = "UI")
	float GetHealthPercent();

	UFUNCTION(BlueprintCallable, Category = "UI")
	FString GetAmmoDataText();

	UFUNCTION(BlueprintCallable, Category = "UI")
	bool GetWeaponUIData(FWeaponUIData& UIData);

	UFUNCTION(BlueprintCallable, Category = "UI")
	bool GetWeaponAmmoData(FAmmoData& AmmoData);

	UFUNCTION(BlueprintCallable, Category = "UI")
	bool IsPlayerAlive() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	bool IsPlayerSpectating() const;
	
};

