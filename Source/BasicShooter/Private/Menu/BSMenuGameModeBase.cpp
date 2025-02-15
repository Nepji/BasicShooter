// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/BSMenuGameModeBase.h"

#include "Menu/BSMenuGameHUD.h"

ABSMenuGameModeBase::ABSMenuGameModeBase()
{
	PlayerControllerClass = ABSMenuGameModeBase::StaticClass();
	HUDClass = ABSMenuGameHUD::StaticClass();
}