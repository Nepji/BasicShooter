// Fill out your copyright notice in the Description page of Project Settings.

#include "Menu/BSMenuWidget.h"

#include "BSBaseGameInstance.h"
#include "Components/Button.h"
#include "Components/HorizontalBox.h"
#include "Kismet/GameplayStatics.h"
#include "Menu/BSMenuLevelItemWidget.h"
void UBSMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if (StartGameButton)
	{
		StartGameButton->OnClicked.AddDynamic(this, &UBSMenuWidget::OnStartGame);
	}

	if (QuitGameButton)
	{
		QuitGameButton->OnClicked.AddDynamic(this, &UBSMenuWidget::OnQuitGame);
	}

	InitLevelItems();
}
void UBSMenuWidget::OnAnimationFinished_Implementation(const UWidgetAnimation* Animation)
{
	if(Animation != HideAnimation)
	{
		return;
	}
	
	const auto BSGameInstance = GetBaseGameInstance();
	if(!BSGameInstance)
	{
		return;
	}
	
	UGameplayStatics::OpenLevel(this, BSGameInstance->GetStartupLevel().LevelName);
}
void UBSMenuWidget::OnStartGame()
{
	PlayAnimation(HideAnimation);
}
void UBSMenuWidget::OnQuitGame()
{
	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}
void UBSMenuWidget::InitLevelItems()
{
	const auto BSGameInstance = GetBaseGameInstance();
	if(!BSGameInstance)
	{
		return;
	}
	checkf(BSGameInstance->GetLevelsData().Num() != 0, TEXT("Must be at least 1 Game Level"));

	if(!LevelItemBox)
	{
		return;
	}
	LevelItemBox->ClearChildren();

	for(auto LevelData : BSGameInstance->GetLevelsData())
	{
		const auto LevelItemWidget = CreateWidget<UBSMenuLevelItemWidget>(GetWorld(),LevelItemWidgetClass);
		if(!LevelItemWidget)
		{
			continue;
		}
		LevelItemWidget->SetLevelData(LevelData);
		LevelItemWidget->OnLevelSelected.AddUObject(this,&UBSMenuWidget::OnLevelSelected);

		LevelItemBox->AddChild(LevelItemWidget);
		LevelItemWidgets.Add(LevelItemWidget);
	}


	if(BSGameInstance->GetStartupLevel().LevelName.IsNone() || BSGameInstance->GetStartupLevel().LevelName == "Name")
	{
		OnLevelSelected(BSGameInstance->GetLevelsData()[0]);
	}
	else
	{
		OnLevelSelected(BSGameInstance->GetStartupLevel());
	}
}
void UBSMenuWidget::OnLevelSelected(const FLevelData& Data)
{
	const auto BSGameInstance = GetBaseGameInstance();
	if(!BSGameInstance)
	{
		return;
	}
	BSGameInstance->SetStartupLevel(Data);

	for(auto LevelItemWidget : LevelItemWidgets)
	{
		if(LevelItemWidget)
		{
			const auto IsSelected = Data.LevelName == LevelItemWidget->GetLevelData().LevelName;
			LevelItemWidget->SetSelected(IsSelected);
		}
	}
}
UBSBaseGameInstance* UBSMenuWidget::GetBaseGameInstance() const
{
	if(!GetWorld())
	{
		return nullptr;
	}
	return GetWorld()->GetGameInstance<UBSBaseGameInstance>();
}