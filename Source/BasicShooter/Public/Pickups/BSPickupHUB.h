// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BSBasePickup.h"
#include "GameFramework/Actor.h"
#include "BSPickupHUB.generated.h"

UCLASS()
class BASICSHOOTER_API ABSPickupHUB : public AActor
{
	GENERATED_BODY()
	
public:	
	ABSPickupHUB();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly,Category = "Pickup")
	TArray<TSubclassOf<ABSBasePickup>> Pickups;

	UPROPERTY(EditDefaultsOnly,Category = "Pickup", meta = (ClampMin = 0))
	float RespawnRate = 3.0f;

	UPROPERTY(EditDefaultsOnly,Category = "Pickup")
	bool Random = false;
public:	
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY()
	ABSBasePickup* CurrentPickup;

	
	int32 CurrentPickupIndex = 0;
	FTimerHandle PickupRespawnTimerHandle;

private:
	void SpawnPickup();
	void OnPickupTaken();

};
