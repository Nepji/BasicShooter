// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/BSGameOverHUDWidget.h"

#include "BSBaseGameInstance.h"
#include "BSGameModeBase.h"
#include "BSPlayerState.h"
#include "Components/Button.h"
#include "GameFramework/GameModeBase.h"
#include "..\..\Public\UI\BSPlayersStatRowWidget.h"
#include "Components/VerticalBox.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetTextLibrary.h"


void UBSGameOverHUDWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if (RestartButton)
	{
		RestartButton->OnClicked.AddDynamic(this, &UBSGameOverHUDWidget::OnRestart);
	}

	if (MainMenuButton)
	{
		MainMenuButton->OnClicked.AddDynamic(this, &UBSGameOverHUDWidget::OnMainMenu);
	}	

	if(GetWorld())
	{
		const auto GameMode = Cast<ABSGameModeBase>(GetWorld()->GetAuthGameMode());
		if(GameMode)
		{
			GameMode->OnMatchStateChanged.AddUObject(this, &UBSGameOverHUDWidget::OnMatchStateChanged);
		}
	}
}
void UBSGameOverHUDWidget::OnRestart()
{
	const auto CurrentLevelName = UGameplayStatics::GetCurrentLevelName(this);
	UGameplayStatics::OpenLevel(this, FName(CurrentLevelName));
}
void UBSGameOverHUDWidget::OnMainMenu()
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
void UBSGameOverHUDWidget::OnMatchStateChanged(const EBSMatchState State)
{
	if(State == EBSMatchState::GameOver)
	{
		UpdatePlayerStat();
	}
}
void UBSGameOverHUDWidget::UpdatePlayerStat()
{
	if(!GetWorld() || !GetWorld()->GetAuthGameMode())
	{
		return;
	}

	PlayerStatBox->ClearChildren();

	for(auto It = GetWorld()->GetControllerIterator();It;++It)
	{
		const auto Controller = It->Get();
		if(!Controller)
		{
			continue;
		}

		const auto PlayerState = Cast<ABSPlayerState>(Controller->PlayerState);
		if(!PlayerState)
		{
			continue;
		}
		
		const auto PlayerStatRowWidget = CreateWidget<UBSPlayersStatRowWidget>(GetWorld(), PlayerStatRowWidgetClass);
		if(!PlayerStatRowWidget)
		{
			continue;
		}

		PlayerStatRowWidget->SetPlayerName(UKismetTextLibrary::Conv_StringToText(PlayerState->GetPlayerName()));
		PlayerStatRowWidget->SetPlayerKills(UKismetTextLibrary::Conv_IntToText(PlayerState->GetKillStat()));
		PlayerStatRowWidget->SetPlayerDeath(UKismetTextLibrary::Conv_IntToText(PlayerState->GetDeathStat()));
		PlayerStatRowWidget->SetPlayerAssists(UKismetTextLibrary::Conv_IntToText(PlayerState->GetAssistsStat()));
		PlayerStatRowWidget->SetPlayerTeam(UKismetTextLibrary::Conv_StringToText(PlayerState->GetTeamName()));
		PlayerStatRowWidget->SetPlayerIndicatorVisibility(Controller->IsPlayerController());

		PlayerStatBox->AddChild(PlayerStatRowWidget);
		
	}
}
