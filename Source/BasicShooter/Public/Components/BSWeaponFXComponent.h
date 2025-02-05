// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BSCoreTypes.h"
#include "Components/ActorComponent.h"
#include "BSWeaponFXComponent.generated.h"

class UNiagaraSystem;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BASICSHOOTER_API UBSWeaponFXComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UBSWeaponFXComponent();

	void PlayImpactFX(const FHitResult& HitResult);

protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "VFX")
	FImpactData DefaultImpactData;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "VFX")
	TMap<UPhysicalMaterial*, FImpactData> ImpactDataMap;
	

		
};
