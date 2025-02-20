﻿// Fill out your copyright notice in the Description page of Project Settings.

#include "BSBaseGameInstance.h"

#include "Sound/BSSoundFunLib.h"
void UBSBaseGameInstance::SetStartupLevel(const FLevelData& Data)
{
	CurrentLevel = Data;
}
FLevelData UBSBaseGameInstance::GetStartupLevel() const
{
	return CurrentLevel;
}
TArray<FLevelData> UBSBaseGameInstance::GetLevelsData()
{
	return  LevelsData;
}
FName UBSBaseGameInstance::GetMenuLevelName() const
{
	return MenuLevelName;
}
void UBSBaseGameInstance::ToggleVolume() const
{
	if(!MasterSoundClass)
	{
		return;
	}
	UBSSoundFunLib::ToggleSoundClassVolume(MasterSoundClass);
}
