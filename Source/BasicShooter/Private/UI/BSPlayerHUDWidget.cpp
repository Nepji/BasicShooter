// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BSPlayerHUDWidget.h"

#include "Components/BSHealthComponent.h"
#include "Components/BSWeaponComponent.h"
#include "Kismet/GameplayStatics.h"
#include "BSCoreUtils.h"
#include "BSGameModeBase.h"
#include "Kismet/KismetTextLibrary.h"

bool UBSPlayerHUDWidget::Initialize()
{
	if (GetOwningPlayer())
	{
		OnNewPawn(GetOwningPlayerPawn());
		GetOwningPlayer()->GetOnNewPawnNotifier().AddUObject(this, &UBSPlayerHUDWidget::OnNewPawn);
	}
	return Super::Initialize();
}
void UBSPlayerHUDWidget::OnNewPawn(APawn* Pawn)
{
	if (const auto HealthComponent = BSCoreUtils::GetActorComponent<UBSHealthComponent>(Pawn))
	{
		if(HealthComponent->OnHealthChange.IsBoundToObject(this))
		{
			 return;
		}
		HealthComponent->OnHealthChange.AddUObject(this, &UBSPlayerHUDWidget::OnHealthChange);
	}
}

float UBSPlayerHUDWidget::GetHealthPercent()
{
	if (const auto HealthComponent = BSCoreUtils::GetActorComponent<UBSHealthComponent>(GetOwningPlayerPawn()))
	{
		return HealthComponent->GetHealthPercent();
	}
	return 0.0f;
}
bool UBSPlayerHUDWidget::GetAmmoDataText(FText& AmmoDataText)
{
	FAmmoData AmmoData;
	if(!GetWeaponAmmoData(AmmoData))
	{
		return false;
	}
	const FString FullCapacityLabel = AmmoData.Infinite?"∞":FString::FromInt(AmmoData.BulletAmount);
	const FString BulletsInClip = FString::FromInt(AmmoData.BulletsInClip);
	
	const auto ResultText = FString::Printf(TEXT("%s  |  %s"),*BulletsInClip,*FullCapacityLabel);
	AmmoDataText = UKismetTextLibrary::Conv_StringToText(ResultText);
	return true;
		
}
bool UBSPlayerHUDWidget::GetWeaponUIData(FWeaponUIData& UIData)
{
	if (const auto WeaponComponent = BSCoreUtils::GetActorComponent<UBSWeaponComponent>(GetOwningPlayerPawn()))
	{
		return WeaponComponent->GetWeaponUIData(UIData);
	}
	return false;
}
bool UBSPlayerHUDWidget::GetWeaponAmmoData(FAmmoData& AmmoData)
{
	if (const auto WeaponComponent = BSCoreUtils::GetActorComponent<UBSWeaponComponent>(GetOwningPlayerPawn()))
	{
		return WeaponComponent->GetWeaponAmmoData(AmmoData);
	}
	return false;
}
bool UBSPlayerHUDWidget::IsPlayerAlive() const
{
	if (const auto HealthComponent = BSCoreUtils::GetActorComponent<UBSHealthComponent>(GetOwningPlayerPawn()))
	{
		return !HealthComponent->IsDead();
	}
	return false;
}
bool UBSPlayerHUDWidget::IsPlayerSpectating() const
{
	if (const auto Controller = GetOwningPlayer())
	{
		return Controller->GetStateName() == NAME_Spectating;
	}
	return false;
}
void UBSPlayerHUDWidget::OnHealthChange(float Health, float HealthDelta)
{
	if (HealthDelta > 0.0f)
	{
		OnTakeDamage();
	}
}

bool UBSPlayerHUDWidget::GetPlayerStatistic(FText& PlayerStatisticText) const
{
	if (!GetWorld())
	{
		return false;
	}
	const auto PlayerState = Cast<ABSPlayerState>(GetOwningPlayerState());
	if (!PlayerState)
	{
		return false;
	}
	const auto Kills = PlayerState->GetKillStat();
	const auto Death = PlayerState->GetDeathStat();
	const auto Assists = PlayerState->GetAssistsStat();

	const auto ResultText = FString::Printf(TEXT("%i  |  %i  |  %i"), Kills, Death, Assists);
	PlayerStatisticText = UKismetTextLibrary::Conv_StringToText(ResultText);
	return true;
}
bool UBSPlayerHUDWidget::GetMatchStatistic(FText& MatchStatistic) const
{
	if (!GetWorld())
	{
		return false;
	}
	const auto MatchResult = Cast<ABSGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!MatchResult)
	{
		return false;
	}
	const auto CurrentRound = MatchResult->GetCurrentMatchRound();
	const auto MaxRounds = MatchResult->GetMatchRoundsCount();
	const auto ResultText = FString::Printf(TEXT("%i  |  %i"), CurrentRound, MaxRounds);
	MatchStatistic = UKismetTextLibrary::Conv_StringToText(ResultText);
	return true;
}
bool UBSPlayerHUDWidget::GetRoundRemainingTime(FText& RoundRemainingTimeText) const
{
	if (!GetWorld())
	{
		return false;
	}
	const auto MatchResult = Cast<ABSGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!MatchResult)
	{
		return false;
	}

	const auto TimeRemaining = MatchResult->GetRoundCountDown();
	constexpr auto SecondsPerMinute = 60;
	const auto Seconds = TimeRemaining % SecondsPerMinute;
	const auto Minutes = FMath::Floor(TimeRemaining / SecondsPerMinute);
	const auto ResultText = FString::Printf(TEXT("%i : %i"), Minutes, Seconds);
	RoundRemainingTimeText = UKismetTextLibrary::Conv_StringToText(ResultText);
	return true;
}