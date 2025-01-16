// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AssetActionUtility.h"
#include "CoreMinimal.h"
#include "AssetUtility.generated.h"

UCLASS(BlueprintType,Blueprintable)
class BASICSHOOTER_API UAssetUtility : public UAssetActionUtility
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void SetPrefix();

	UFUNCTION(BlueprintCallable)
	void RenameAt(const FString From,const FString To);
	

	UFUNCTION(BlueprintCallable)
	TArray<UObject*> SelectedAssetsArray();

protected:

	FString NewNameWithPrefix(UObject* Obj);
	FString NewPrefix(UObject* Obj);
	bool ExistedPrefix(const FString& OldName);
	bool ExistedCorrectPrefix(const FString& OldName,const FString& CorrectPrefix);
	FString ChangedPrefix(FString Name, const FString &CorrectPrefix);

protected:
	UPROPERTY(Blueprintable)
	TMap<FString, FString> AssetClassToPrefixMap = {
		{"Material", "M_"},
		{"MaterialInstance", "MI_"},
		{"MaterialInstanceConstant", "MI_"},
		{"MaterialFunction", "MF_"},
		{"Texture", "T_"},
		{"Texture2D", "T_"},
		{"TextureCube", "T_"},
		{"StaticMesh", "SM_"},
		{"SkeletalMesh", "SK_"},
		{"AnimSequence", "AS_"},
		{"Blueprint", "BP_"},
		{"SoundWave", "SW_"},
		{"SoundCue", "SCue_"},
		{"Level", "LVL_"},
		{"World", "WRLD_"},
		{"ParticleSystem", "PS_"},
		{"NiagaraSystem", "FXS_"},
		{"NiagaraEmitter", "FXE_"},
		{"NiagaraFunction", "FXF_"},
		{"PhysicsAsset", "PHYS_"},
		{"PhysicsMaterial", "PM_"},
		{"PostProcessMaterial", "PPM_"},
		{"Skeleton", "SKEL_"},
		{"Montages", "AM_"},
		{"BlendSpace", "BS_"},
		{"AnimationBlueprint", "ABP_"},
		{"WidgetBlueprint", "WBP_"},
		{"DataTable", "DT_"},
		{"CurveTable", "CT_"},
		{"Enum", "E_"},
		{"Structure", "F_"},
		{"Rig", "Rig_"},
		{"ActorComponent", "AC_"},
		{"BlueprintInterface", "BI_"},
		{"LevelSequence", "LS_"},
		{"SequencerEdits", "EDIT_"},
		{"MediaSource", "MS_"},
		{"MediaOutput", "MO_"},
		{"MediaPlayer", "MP_"},
		{"MediaProfile", "MPR_"},
		{"LevelSnapshots", "SNAP_"},
		{"RemoteControlPreset", "RCP_"},
		{"NDisplayConfiguration", "NDC_"},
		{"OCIOProfile", "OCIO_"},
		{"HDRI", "HDR_"}
	};

	
};
