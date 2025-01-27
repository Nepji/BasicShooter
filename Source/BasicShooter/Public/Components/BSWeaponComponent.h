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
	void NextWeapon();
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "Weapon")
	TArray<TSubclassOf<ABSBaseWeapon>> WeaponClasses;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "Weapon")
	FName WeaponAttachSocket = "WeaponSocket";

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "Weapon")
	FName WeaponArmorySocket = "ArmorySocket";

	//We need one more Armory for Pistol or tiny weapon
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "Weapon")
	FName WeaponSecondaryArmorySocket = "SecondaryArmorySocket";
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	ABSBaseWeapon* CurrentWeapon;

	UPROPERTY()
	TArray<ABSBaseWeapon*> Weapons;

	int32 CurrentWeaponIndex = 0;

private:
	void AttachWeaponToSocket(ABSBaseWeapon* Weapon, USkeletalMeshComponent* SceneComponent, FName SocketName);
	void EquipWeapon(int32 WeaponIndex);
	void SpawnWeapon();

		
};
