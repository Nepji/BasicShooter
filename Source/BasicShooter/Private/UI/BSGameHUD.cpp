// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BSGameHUD.h"

void ABSGameHUD::DrawHUD()
{
	Super::DrawHUD();
}
void ABSGameHUD::BeginPlay()
{
	Super::BeginPlay();
	auto PlayerHudWidget = CreateWidget<UUserWidget>(GetWorld(),PlayerHUDWidgetClass);
	if(PlayerHudWidget)
	{
		PlayerHudWidget->AddToViewport();
	}
}