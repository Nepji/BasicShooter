// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/BSSpectatorHUDWidget.h"

#include "BSCoreUtils.h"
#include "BSGameModeBase.h"
#include "Components/BSHealthComponent.h"
#include "Components/BSRespawnComponent.h"
#include "Kismet/KismetTextLibrary.h"
bool UBSSpectatorHUDWidget::GetRespawnTimeRemaining(FText& TimeRemaining)
{
	if (!GetWorld())
	{
		return false;
	}
	const auto GameMode = Cast<ABSGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode || !GameMode->CanRespawn())
	{
		return false;
	}
	const auto RespawnComponent = BSCoreUtils::GetActorComponent<UBSRespawnComponent>(GetOwningPlayer());
	if (!RespawnComponent)
	{
		return false;
	}
	const auto RespawnRemaining = RespawnComponent->RespawnTimeRemaining();
	TimeRemaining = UKismetTextLibrary::Conv_IntToText(RespawnRemaining);
	return true;
}
bool UBSSpectatorHUDWidget::GetRandomTip(FText& TipText)
{
	if (!GetWorld() || RowTipsNames.IsEmpty())
	{
		return false;
	}
	
	const auto Tip = TipsDataRowHandle.DataTable->FindRow<FTipsData>(RowTipsNames[CurrentTipID],TEXT("Tip"));
	TipText = UKismetTextLibrary::Conv_StringToText(Tip->TipDescription);
	return true;
}
bool UBSSpectatorHUDWidget::Initialize()
{
	const auto InitStatus = Super::Initialize();
	if (InitStatus && GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(NextTipTimerHandle, this, &UBSSpectatorHUDWidget::NextTip, TipTimeOnScreen, true);
	}
	return InitStatus;
}
void UBSSpectatorHUDWidget::NextTip()
{
	if(TipsDataRowHandle.IsNull() || !TipsDataRowHandle.DataTable)
	{
		return;
	}
	RowTipsNames = TipsDataRowHandle.DataTable->GetRowNames();
	CurrentTipID = FMath::RandRange(0,RowTipsNames.Num());
}