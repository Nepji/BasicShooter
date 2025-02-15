// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BSGameHUD.h"

#include "BSGameModeBase.h"

void ABSGameHUD::DrawHUD()
{
	Super::DrawHUD();
}
void ABSGameHUD::BeginPlay()
{
	Super::BeginPlay();

	check(PlayerHUDWidgetClass);
	check(PlayerPauseWidgetClass);
	check(GameOverWidgetClass);
	
	GameWidgets.Add(EBSMatchState::InProgress, CreateWidget<UUserWidget>(GetWorld(),PlayerHUDWidgetClass));
	GameWidgets.Add(EBSMatchState::Pause, CreateWidget<UUserWidget>(GetWorld(),PlayerPauseWidgetClass));
	GameWidgets.Add(EBSMatchState::GameOver, CreateWidget<UUserWidget>(GetWorld(),GameOverWidgetClass));
	

	for(const auto GameWidgetPair : GameWidgets)
	{
		const auto GameWidget = GameWidgetPair.Value;
		if(!GameWidget)
		{
			continue;
		}
		GameWidget->AddToViewport();
		GameWidget->SetVisibility(ESlateVisibility::Hidden);
	}

	if(GetWorld())
	{
		const auto GameMode = Cast<ABSGameModeBase>(GetWorld()->GetAuthGameMode());
		if(GameMode)
		{
			GameMode->OnMatchStateChanged.AddUObject(this, &ABSGameHUD::OnMatchStateChanged);
		}
	}
}
void ABSGameHUD::OnMatchStateChanged(EBSMatchState State)
{
	if(CurrentWidget)
	{
		CurrentWidget->SetVisibility(ESlateVisibility::Hidden);
	}
	if(GameWidgets.Contains(State))
	{
		CurrentWidget = GameWidgets[State];
		CurrentWidget->SetVisibility(ESlateVisibility::Visible);
	}
}