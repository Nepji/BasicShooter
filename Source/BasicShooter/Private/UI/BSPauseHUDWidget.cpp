// Fill out your copyright notice in the Description page of Project Settings.

#include "..\..\Public\UI\BSPauseHUDWidget.h"

#include "BSBaseGameInstance.h"
#include "Components/Button.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"
void UBSPauseWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if(ClearPauseButton)
	{
		ClearPauseButton->OnClicked.AddDynamic(this,&UBSPauseWidget::OnClearPause);
	}

	if(MainMenuButton)
	{
		MainMenuButton->OnClicked.AddDynamic(this,&UBSPauseWidget::OnMainMenu);
	}
}
void UBSPauseWidget::OnClearPause()
{
	if (!GetWorld() || !GetWorld()->GetAuthGameMode())
	{
		return;
	}
	GetWorld()->GetAuthGameMode()->ClearPause();
}
void UBSPauseWidget::OnMainMenu()
{
	if(!GetWorld())
	{
		return;
	}
	const auto Instance = Cast<UBSBaseGameInstance>(GetWorld()->GetGameInstance());
	if(Instance->GetMenuLevelName().IsNone())
	{
		return;
	}
	UGameplayStatics::OpenLevel(this, Instance->GetMenuLevelName());
}