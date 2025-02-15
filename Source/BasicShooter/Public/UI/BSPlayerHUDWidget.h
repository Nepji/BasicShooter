// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BSCoreTypes.h"
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

public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	float GetHealthPercent();

	UFUNCTION(BlueprintCallable, Category = "UI")
	bool GetAmmoDataText(FText& AmmoDataText);

	UFUNCTION(BlueprintCallable, Category = "UI")
	bool GetWeaponUIData(FWeaponUIData& UIData);

	UFUNCTION(BlueprintCallable, Category = "UI")
	bool GetWeaponAmmoData(FAmmoData& AmmoData);

	UFUNCTION(BlueprintCallable, Category = "UI")
	bool IsPlayerAlive() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	bool IsPlayerSpectating() const;

	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
	void OnTakeDamage();

	UFUNCTION(BlueprintCallable, Category = "UI")
	bool GetPlayerStatistic(FText& PlayerStatisticText) const; 

	UFUNCTION(BlueprintCallable, Category = "UI")
	bool GetMatchStatistic(FText& MatchStatistic) const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	bool GetRoundRemainingTime(FText& RoundRemainingTimeText) const;


	virtual void NativeOnInitialized() override;

private:
	void OnNewPawn(APawn* Pawn);
	void OnHealthChange(float Health, float HealthDelta);
	
};

