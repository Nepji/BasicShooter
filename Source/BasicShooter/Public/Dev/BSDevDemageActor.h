// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BSDevDemageActor.generated.h"

UCLASS()
class BASICSHOOTER_API ABSDevDamegeActor : public AActor
{
	GENERATED_BODY()


public:
	UPROPERTY(Blueprintable)
	USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere,Blueprintable, meta = (ClampMin = -1))
	float Radius = 10.0f;

	UPROPERTY(EditAnywhere,Blueprintable)
	FColor SphereColor = FColor::Cyan;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 0.0f))
	float Damage = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool CentreFullDamage = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Heal = false;
public:	
	ABSDevDamegeActor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
