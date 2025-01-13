// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BSBaseWeapon.generated.h"

UCLASS()
class BASICSHOOTER_API ABSBaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	ABSBaseWeapon();

	virtual void Fire();

protected:
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category = "Components")
	UStaticMeshComponent* MeshComponent;
protected:
	virtual void BeginPlay() override;



};
