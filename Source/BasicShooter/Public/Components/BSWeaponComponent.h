// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Weapon/BSBaseWeapon.h"
#include "BSWeaponComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BASICSHOOTER_API UBSWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UBSWeaponComponent();

	void StartFire();
	void StopFire();

protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "Weapon")
	TSubclassOf<ABSBaseWeapon> WeaponClass;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "Weapon")
	FName WeaponAttachSocket;
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	ABSBaseWeapon* CurrentWeapon;
	void SpawnWeapon();

		
};
