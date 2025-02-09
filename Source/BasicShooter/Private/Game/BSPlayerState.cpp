// Fill out your copyright notice in the Description page of Project Settings.

#include "..\..\Public\Game\BSPlayerState.h"

DEFINE_LOG_CATEGORY_STATIC(LogPlayerState, All, All);

void ABSPlayerState::SetTeamID(int32 ID)
{
	TeamID = ID;
}
int32 ABSPlayerState::GetTeamID() const
{
	return TeamID;
}
void ABSPlayerState::SetTeamColor(FLinearColor Color)
{
	TeamColor = Color;
}
FLinearColor ABSPlayerState::GetTeamColor() const
{
	return TeamColor;
}
void ABSPlayerState::SetTeamName(FString Name)
{
	TeamName = Name;
}
FString ABSPlayerState::GetTeamName()
{
	return TeamName;
}
void ABSPlayerState::AddKill()
{
	KillsNum++;
}
int32 ABSPlayerState::GetKillStat() const
{
	return KillsNum;
}
void ABSPlayerState::AddAssist()
{
	AssistNum++;
}
int32 ABSPlayerState::GetAssistsStat() const
{
	return AssistNum;
}
void ABSPlayerState::AddDeath()
{
	DeathNum++;
}
int32 ABSPlayerState::GetDeathStat() const
{
	return DeathNum;
}
void ABSPlayerState::LogInfo() const
{
	UE_LOG(LogPlayerState, Display, TEXT("TeamID: %i, Team Name: %s, Kills: %i, Deaths: %i"),TeamID,*TeamName,KillsNum,DeathNum);
}