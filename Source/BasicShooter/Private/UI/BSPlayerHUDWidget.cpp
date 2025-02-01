// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BSPlayerHUDWidget.h"

#include "Components/BSHealthComponent.h"
#include "Kismet/GameplayStatics.h"

float UBSPlayerHUDWidget::GetHealthPercent() const
{
	const auto PlayerPawn = GetOwningPlayerPawn();
	if (!PlayerPawn)
	{
		return 0.0f;
	}
	const auto Component = PlayerPawn->GetComponentByClass(UBSHealthComponent::StaticClass());
	if (!Component)
	{
		return 0.0f;
	}
	const auto HealthComponent = Cast<UBSHealthComponent>(Component);
	return HealthComponent->GetHealthPercent();
}