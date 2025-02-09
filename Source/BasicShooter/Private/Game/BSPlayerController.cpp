// Fill out your copyright notice in the Description page of Project Settings.

#include "BSPlayerController.h"

#include "Components/BSRespawnComponent.h"

ABSPlayerController::ABSPlayerController()
{
	RespawnComponent = CreateDefaultSubobject<UBSRespawnComponent>("RespawnComponents");
}
void ABSPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	OnNewPawn.Broadcast(InPawn);
}