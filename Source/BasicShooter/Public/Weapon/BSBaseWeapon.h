// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BSBaseWeapon.generated.h"


UCLASS()
class BASICSHOOTER_API ABSBaseWeapon  : public AActor
{
	GENERATED_BODY()

public:
	ABSBaseWeapon();

	virtual void StartFire();
	virtual void StopFire();
	virtual void MakeShot();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FName MuzzleSocketName = "MuzzleSocket";

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = 0))
	float TraceMaxDistance = 1000.0f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float Damage = 10.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = 0))
	float SprayRadius = 1.5f;
protected:
	virtual void BeginPlay() override;

	APlayerController* GetPlayerController() const;
	bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation);
	FVector			   GetMuzzleWorldLocation() const;
	bool			   GetTraceData(FVector& TraceStart, FVector& TraceEnd);
	void			   MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd) const;
	


	
};
