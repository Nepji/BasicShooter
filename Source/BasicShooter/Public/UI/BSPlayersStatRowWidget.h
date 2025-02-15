// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BSPlayersStatRowWidget.generated.h"

class UTextBlock;
class UImage;

UCLASS()
class BASICSHOOTER_API UBSPlayersStatRowWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void SetPlayerName(const FText& Text) const;
	void SetPlayerKills(const FText& Text) const;
	void SetPlayerDeath(const FText& Text) const;
	void SetPlayerAssists(const FText& Text) const;
	void SetPlayerTeam(const FText& Text) const;
	void SetPlayerIndicatorVisibility(bool Visible) const; 

	
protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* PlayerNameTextBlock;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* PlayerKillsTextBlock;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* PlayerDeathTextBlock;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* PlayerAssistsTextBlock;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* PlayerTeamTextBlock;

	UPROPERTY(meta = (BindWidget))
	UImage* PlayerIndicatorVisibility;
};
