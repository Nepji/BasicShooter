// Fill out your copyright notice in the Description page of Project Settings.

#include "Menu/BSMenuPlayerController.h"
void ABSMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();


	SetInputMode(FInputModeUIOnly());
	bShowMouseCursor = true;
}