// Fill out your copyright notice in the Description page of Project Settings.

#include "Menu/BSMenuGameHUD.h"

#include "Blueprint/UserWidget.h"
#include "UI/BSBaseWidget.h"
void ABSMenuGameHUD::BeginPlay()
{
	Super::BeginPlay();

	if(MenuWidgetClass)
	{
		if(const auto MenuWidget = CreateWidget<UBSBaseWidget>(GetWorld(),MenuWidgetClass))
		{
			MenuWidget->AddToViewport();
			MenuWidget->Show();
		}
	}

}