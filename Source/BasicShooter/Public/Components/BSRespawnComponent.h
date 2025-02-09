// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BSRespawnComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BASICSHOOTER_API UBSRespawnComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UBSRespawnComponent();
	void Respawn(int32 RespawnTime);
	int32 RespawnTimeRemaining() const;

protected:
 virtual void BeginPlay() override;;

private:
	FTimerHandle RespawnTimerHandle;
	int32 RespawnCountDown = 0;

private:
	void RespawnTimerUpdate();

};
