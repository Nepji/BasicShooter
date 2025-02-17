#pragma once

#include "EnhancedInputSubsystemInterface.h"
#include "NiagaraSystem.h"
#include "Runtime/Engine/Classes/Engine/DataTable.h"
#include "BSCoreTypes.generated.h"


// DELEGATE
//
// Weapon
DECLARE_MULTICAST_DELEGATE(FOnClipEmptySignature)
// AnimNotify
DECLARE_MULTICAST_DELEGATE_OneParam(FOnNotifiedSignature, USkeletalMeshComponent*)
//Health
DECLARE_MULTICAST_DELEGATE(FOnDeath)
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnHealthChange,float,float)
//Pickup
DECLARE_MULTICAST_DELEGATE(FOnPickupTakenSignature)
//GameMode
DECLARE_TS_MULTICAST_DELEGATE_OneParam(FOnMatchStateChangedSignature, EBSMatchState);
//Menu
DECLARE_MULTICAST_DELEGATE_OneParam(FOnLevelSelectedSignature, const FLevelData&)
//
// STRUCT
//Input
USTRUCT(Blueprintable)
struct FInputData
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	UInputMappingContext* MappingContext;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	UInputAction* MoveAction;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	UInputAction* LookAround;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	UInputAction* JumpAction;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	UInputAction* RunAction;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	UInputAction* FireAction;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	UInputAction* NextWeaponAction;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	UInputAction* ReloadAction;
};
// Weapon
USTRUCT(Blueprintable)
struct FAmmoData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapom", meta = (EditCondition = "!Infinite"))
	int32 BulletAmount = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapom")
	int32 BulletsInClip = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapom", meta = (ToolTip = "Infinite bullets"))
	bool Infinite = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapom", meta = (ToolTip = "All remaining bullets in clip while reload are not returned"))
	bool IgnoreRemainingBullets = false;
};

USTRUCT(Blueprintable)
struct FWeaponUIData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "UI")
	UTexture2D* MainIcon = nullptr;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "UI")
	UTexture2D* CrossHairIcon = nullptr;
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
// VFX
USTRUCT(Blueprintable)
struct FDecalData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	UMaterialInterface* Material = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	FVector Size = FVector(10.0f);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	float LifeTime = 5.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	float FadeOutTime = 0.7f;
};
USTRUCT(Blueprintable)
struct FImpactData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	UNiagaraSystem* NiagaraEffect = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	FDecalData DecalData;
};
// GameMode
USTRUCT(Blueprintable)
struct FTeamData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly,Blueprintable)
	FString TeamName;
	
	UPROPERTY(EditDefaultsOnly,Blueprintable)
	FLinearColor TeamColor = FLinearColor::Green;
};
USTRUCT(Blueprintable)
struct FGameData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "Game", meta = (ClampMin = 1, ClampMax = 100))
	int32 PlayerNum = 2;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	bool BotsEnabled = false;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "Game", meta = (ClampMin = 1, ClampMax = 99))
	int32 RoundNum = 4;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "Game", meta = (ClampMin = 1, ClampMax = 99999))
	int32 RoundTime = 120; // In Seconds

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "Game", meta = (ClampMin = 1, ClampMax = 99999))
	int32 RespawnRate = 3.0f; // In Seconds

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "Game")
	FTeamData DefaultTeamData;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "Game")
	TArray<FTeamData> TeamsData;
};
UENUM(Blueprintable)
enum class EBSMatchState : uint8
{
	WaitingToStart,
	Pause,
	InProgress,
	GameOver,
};

// Data
USTRUCT(BlueprintType)
struct FTipsData : public FTableRowBase
{
	GENERATED_BODY();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString TipTitle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString TipDescription;
};
//Menu

USTRUCT(Blueprintable)
struct FLevelData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "Game")
	FName LevelName = NAME_Name;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "Game")
	FName DisplayLevelName = NAME_Name;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "Game")
	UTexture2D* LevelThumb = nullptr;
};

 