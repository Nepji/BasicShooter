// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BSCoreTypes.h"
#include "Components/BSWeaponFXComponent.h"
#include "GameFramework/Actor.h"
#include "BSBaseWeapon.generated.h"





UCLASS()
class BASICSHOOTER_API ABSBaseWeapon : public AActor
{
	GENERATED_BODY()

public:
	FOnClipEmptySignature OnClipEmptySignature;

public:
	ABSBaseWeapon();
	
	virtual void StartFire();
	virtual void StopFire();
	virtual void MakeShot();
	virtual bool CanReload();
	virtual void Reload();
	FWeaponUIData GetUIData() const;
	FAmmoData GetAmmoData() const;
	bool TryAddAmmo(int32 AmountOfAmmo);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	FName MuzzleSocketName = "MuzzleSocket";

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = 0), Category = "Weapon")
	float TraceMaxDistance = 1000.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float Damage = 10.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = 0), Category = "Weapon")
	float SprayRadius = 1.5f;

	UPROPERTY(EditDefaultsOnly, Blueprintable, Category = "Weapon")
	FAmmoData DefaultAmmo{ 30, 30, false, false};

	UPROPERTY(EditDefaultsOnly, Blueprintable, Category = "Weapon")
	FWeaponUIData UIData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	UBSWeaponFXComponent* WeaponFXComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	UNiagaraSystem* MuzzleFX;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	UNiagaraSystem* TraceFX;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	FString TraceTargetName = "TraceTarget";
	
protected:
	virtual void BeginPlay() override;

	APlayerController* GetPlayerController() const;
	bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation);
	FVector GetMuzzleWorldLocation() const;
	bool GetTraceData(FVector& TraceStart, FVector& TraceEnd);
	
	void MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd) const;

	void DecreaseAmmo();
	void ChangeClip();
	void LogAmmo();
	bool IsAmmoEmpty() const;
	bool IsClipEmpty() const;
	bool IsAmmoFull() const;
	void SpawnTraceFX(const FVector& TraceStart, const FVector& TraceEnd);
	UNiagaraComponent* SpawnMuzzleFX();
	

private:
	FAmmoData CurrentAmmo;
	
};
