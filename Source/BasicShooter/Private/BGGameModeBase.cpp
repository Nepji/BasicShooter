// Fill out your copyright notice in the Description page of Project Settings.


#include "BGGameModeBase.h"

#include "Player/BSBaseCharacter.h"
#include "Player/BSPlayerController.h"

ABGGameModeBase::ABGGameModeBase()
{
	DefaultPawnClass = ABSBaseCharacter::StaticClass();
	PlayerControllerClass = ABSPlayerController::StaticClass();
}