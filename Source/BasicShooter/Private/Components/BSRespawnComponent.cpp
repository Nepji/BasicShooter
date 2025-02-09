// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/BSRespawnComponent.h"

#include "BSGameModeBase.h"

UBSRespawnComponent::UBSRespawnComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}
void UBSRespawnComponent::Respawn(int32 RespawnTime)
{
	if (!GetWorld())
	{
		return;
	}
	RespawnCountDown = RespawnTime;
	GetWorld()->GetTimerManager().SetTimer(RespawnTimerHandle, this, &UBSRespawnComponent::RespawnTimerUpdate, 1.0f, true);
}
int32 UBSRespawnComponent::RespawnTimeRemaining() const
{
	return RespawnCountDown;
}
void UBSRespawnComponent::BeginPlay()
{
	Super::BeginPlay();
}
void UBSRespawnComponent::RespawnTimerUpdate()
{
	if(--RespawnCountDown > 0)
	{
		return;
	}
	if(!GetWorld())
	{
		return;
	}
	GetWorld()->GetTimerManager().ClearTimer(RespawnTimerHandle);

	const auto GameMode = Cast<ABSGameModeBase>(GetWorld()->GetAuthGameMode());
	if(!GameMode)
	{
		return;
	}
	GameMode->RespawnRequest(Cast<AController>(GetOwner()));
	
}
