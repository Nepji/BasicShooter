// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BSWeaponFXComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "BSProjectile.generated.h"


class USoundCue;


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

	UPROPERTY(EditDefaultsOnly)
	float ProjectileLifeSpan = 10.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float DamageAmount = 50.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float DamageRadius = 50.0f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	bool CentreFullDamage = true;

	UPROPERTY(EditDefaultsOnly, Category = "VFX")
	UBSWeaponFXComponent* WeaponFXComponent;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "Sound")
	USoundCue* ImpactSound = nullptr;
protected:
	UFUNCTION()
	void OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	virtual void BeginPlay() override;

	AController* GetController() const;


private:
	FVector ShotDirection;
	FTimerHandle ProjectileLifeSpanHandle;

private:
	void LifeSpanOver();
};
