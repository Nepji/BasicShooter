// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BSCoreTypes.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "BSBasePickup.generated.h"

class USoundCue;

UCLASS()
class BASICSHOOTER_API ABSBasePickup : public AActor
{
	GENERATED_BODY()

public:
	FOnPickupTakenSignature OnPickupTakenSignature;

public:
	ABSBasePickup();
	virtual void Tick(float DeltaTime) override;
	bool CouldBeTaken() const;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Pickup")
	USphereComponent* CollisionComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Pickup")
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "Sound")
	USoundCue* PickupSound = nullptr;

protected:
	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual bool PickUpTo(APawn* PlayerPawn);

private:
	float RotationYaw = 0.0f;

private:
	void GenerateRotationYaw();
};
