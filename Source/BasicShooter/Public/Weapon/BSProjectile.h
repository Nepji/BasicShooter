// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "BSProjectile.generated.h"

UCLASS()
class BASICSHOOTER_API ABSProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	ABSProjectile();
	
public:	
	void SetShotDirection(const FVector& Direction);
	
protected:
	UPROPERTY(EditDefaultsOnly)
	USphereComponent* CollisionComponent;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* MeshComponent;
	
	UPROPERTY(EditDefaultsOnly)
	UProjectileMovementComponent* MovementComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float DamageAmount = 50.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float DamageRadius = 50.0f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	bool CentreFullDamage = true;
protected:
	UFUNCTION()
	void OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	virtual void BeginPlay() override;

	AController* GetController() const; 

private:
	FVector ShotDirection;
};
