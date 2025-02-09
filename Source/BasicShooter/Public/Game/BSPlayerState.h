// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "BSPlayerState.generated.h"

/**
 *
 */
UCLASS()
class BASICSHOOTER_API ABSPlayerState : public APlayerState
{
	GENERATED_BODY()
public:
	void SetTeamID(int32 ID);
	int32 GetTeamID() const;

	void SetTeamColor(FLinearColor Color);
	FLinearColor GetTeamColor() const;

	void SetTeamName(FString Name);
	FString GetTeamName();

	void AddKill();
	int32 GetKillStat() const;

	void AddAssist();
	int32 GetAssistsStat() const;

	void AddDeath();
	int32 GetDeathStat() const;

	void LogInfo() const;

private:
	int32 TeamID;
	FLinearColor TeamColor;

	int32 KillsNum = 0;
	int32 DeathNum = 0;
	int32 AssistNum = 0;
	FString TeamName = "Default";
};
