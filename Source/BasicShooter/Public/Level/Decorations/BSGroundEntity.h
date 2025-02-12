// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "BSGroundEntity.generated.h"

UCLASS()
class BASICSHOOTER_API ABSGroundEntity : public AActor
{
	GENERATED_BODY()

public:
	ABSGroundEntity();

	void OnRoundBegin();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USphereComponent* CollisionComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* MeshComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Entity", meta = (ClampMin = 0))
	int32 FadeTime = 3; // In seconds

protected:
	virtual void BeginPlay() override;

private:
	int32 TimerCountDown;
	FTimerHandle FEntityFadeTimerHandle;

private:
	void TimerUpdate();
};
