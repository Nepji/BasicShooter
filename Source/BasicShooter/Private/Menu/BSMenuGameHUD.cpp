// Fill out your copyright notice in the Description page of Project Settings.

#include "Menu/BSMenuGameHUD.h"

#include "Blueprint/UserWidget.h"
void ABSMenuGameHUD::BeginPlay()
{
	Super::BeginPlay();

	if(MenuWidgetClass)
	{
		if(const auto MenuWidget = CreateWidget<UUserWidget>(GetWorld(),MenuWidgetClass))
		{
			MenuWidget->AddToViewport();
		}
	}

}