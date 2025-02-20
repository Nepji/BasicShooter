// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Weapon/BSBaseWeapon.h"
#include "BSWeaponComponent.generated.h"

class USoundCue;

USTRUCT(Blueprintable)
struct FWeaponData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<ABSBaseWeapon> WeaponClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	UAnimMontage* ReloadAnimation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	bool Replaceable = false;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
	USoundCue* ReloadSound;


	bool operator==(const FWeaponData& Data) const
	{
		return Data.WeaponClass == this->WeaponClass;
	}
};


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BASICSHOOTER_API UBSWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UBSWeaponComponent();

	virtual void StartFire();
	virtual void StopFire();
	virtual void NextWeapon();
	bool CanFire() const;
	bool CanReload() const;
	bool IsWeaponsNeedToReload() const;
	bool IsCurrentWeaponEmpty(const ABSBaseWeapon* Weapon) const;
	float GetCurrentAmmoLoadPercent() const;
	void Reload();
	bool GetWeaponUIData(FWeaponUIData& UIData) const;
	bool GetWeaponAmmoData(FAmmoData& AmmoData) const;
	
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	bool TryToAddAmmo(int32 AmountOfAmmo, TSubclassOf<ABSBaseWeapon> WeaponType = nullptr);
	bool TryToRemoveWeapon(FWeaponData& WeaponData);
	bool TryPickupWeapon(const FWeaponData& WeaponData);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	TArray<FWeaponData> WeaponsData;

	/**If need the specific class, that we`ll put in second Armory*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	TArray<TSubclassOf<ABSBaseWeapon>> WeaponsToSecondarySlot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon", meta = (ClampMin = 0))
	int32 MaxEquipWeapons = 2;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	FName WeaponAttachSocket = "WeaponSocket";

	// We need one more Specific Armory for Pistol or other weapon
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	FName WeaponArmorySocket = "ArmorySocket";

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	FName WeaponSecondaryArmorySocket = "SecondaryArmorySocket";

	UPROPERTY(EditDefaultsOnly, Blueprintable, Category = "Animation")
	UAnimMontage* EquipAnimMontage;

	UPROPERTY()
	ABSBaseWeapon* CurrentWeapon;

	UPROPERTY()
	TArray<ABSBaseWeapon*> Weapons;

protected:
	int32 CurrentWeaponIndex = 0;

protected:
	virtual void BeginPlay() override;
	void EquipWeapon(int32 WeaponIndex);

private:
	UPROPERTY()
	UAnimMontage* CurrentReloadAnimation = nullptr;

	UPROPERTY()
	USoundCue* CurrentReloadSound = nullptr;
private:
	bool EquipAnimationInProgress = false;
	bool ReloadAnimationInProgress = false;


private:
	void AttachWeaponToSocket(ABSBaseWeapon* Weapon, USkeletalMeshComponent* SceneComponent, FName SocketName);
	bool SpawnOneWeapon(const FWeaponData& OneWeaponData);
	void SpawnWeapon();
	FName CurrentWeaponSocket(TSubclassOf<ABSBaseWeapon> WeaponClass) const;
	void PlayAnimMontage(UAnimMontage* AnimMontage);
	void InitOneAnimation(const FWeaponData& WeaponData);
	void InitAnimations();
	void OnEquipFinished(USkeletalMeshComponent* MeshComp);
	void OnReloadFinished(USkeletalMeshComponent* MeshComp);
	
	void ChangeClip();
	void OnEmptyClip();

	bool ReplaceableWeapon(FWeaponData& ReplaceableWeaponData);
};

