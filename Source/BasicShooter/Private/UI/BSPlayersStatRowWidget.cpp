// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/BSPlayersStatRowWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
void UBSPlayersStatRowWidget::SetPlayerName(const FText& Text) const
{
	if(PlayerNameTextBlock)
	{
		PlayerNameTextBlock->SetText(Text);
	}
}
void UBSPlayersStatRowWidget::SetPlayerKills(const FText& Text) const
{
	if(PlayerKillsTextBlock)
	{
		PlayerKillsTextBlock->SetText(Text);
	}
}
void UBSPlayersStatRowWidget::SetPlayerDeath(const FText& Text) const
{
	if(PlayerDeathTextBlock)
	{
		PlayerDeathTextBlock->SetText(Text);
	}
}
void UBSPlayersStatRowWidget::SetPlayerAssists(const FText& Text) const
{
	if(PlayerAssistsTextBlock)
	{
		PlayerAssistsTextBlock->SetText(Text);
	}
}
void UBSPlayersStatRowWidget::SetPlayerTeam(const FText& Text) const
{
	if(PlayerTeamTextBlock)
	{
		PlayerTeamTextBlock->SetText(Text);
	}
}
void UBSPlayersStatRowWidget::SetPlayerIndicatorVisibility(const bool Visible) const
{
	if(PlayerIndicatorVisibility)
	{
		PlayerIndicatorVisibility->SetVisibility(Visible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	}
}