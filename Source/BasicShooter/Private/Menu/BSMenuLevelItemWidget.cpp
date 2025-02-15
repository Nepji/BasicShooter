// Fill out your copyright notice in the Description page of Project Settings.

#include "Menu/BSMenuLevelItemWidget.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
void UBSMenuLevelItemWidget::SetLevelData(const FLevelData& Data)
{
	LevelData = Data;

	if(LevelNameTextBlock)
	{
		LevelNameTextBlock->SetText(FText::FromName(Data.DisplayLevelName));
	}

	if(LevelImage)
	{
		LevelImage->SetBrushFromTexture(Data.LevelThumb);
	}
}
FLevelData UBSMenuLevelItemWidget::GetLevelData() const
{
	return LevelData;
}
void UBSMenuLevelItemWidget::SetSelected(bool IsSelected)
{
	if(FrameImage)
	{
		FrameImage->SetVisibility(IsSelected ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	}
}
void UBSMenuLevelItemWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if(LevelSelectButton)
	{
		LevelSelectButton->OnClicked.AddDynamic(this,&UBSMenuLevelItemWidget::OnLevelItemClicked);	
	}
}
void UBSMenuLevelItemWidget::OnLevelItemClicked()
{
	OnLevelSelected.Broadcast(LevelData);
}