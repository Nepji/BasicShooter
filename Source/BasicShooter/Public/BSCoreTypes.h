#pragma once
#include "BSCoreTypes.generated.h"

class ABSBaseWeapon;

// DELEGATE
//
// Weapon
DECLARE_MULTICAST_DELEGATE(FOnClipEmptySignature)
// AnimNotify
DECLARE_MULTICAST_DELEGATE_OneParam(FOnNotifiedSignature, USkeletalMeshComponent*)
	//
	// STRUCT
	//
	// Weapon
	USTRUCT(Blueprintable)
struct FAmmoData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapom", meta = (EditCondition = "!Infinite"))
	int32 BulletAmount;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapom")
	int32 BulletsInClip;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapom", meta = (ToolTip = "Infinite bullets"))
	bool Infinite;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapom", meta = (ToolTip = "All remaining bullets in clip while reload are not returned"))
	bool IgnoreRemainingBullets;
};
USTRUCT(Blueprintable)
struct FWeaponData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<ABSBaseWeapon> WeaponClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	UAnimMontage* ReloadAnimation;
};
// Health Component
USTRUCT(Blueprintable)
struct FHealthData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool Curable = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool AutoHeal = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = 0.0f))
	float HealDelay = 3.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = 0.1f))
	float HealRate = 3.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = 0.0f))
	float HealingValue = 1.0f;
};