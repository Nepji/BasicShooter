// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BSCoreTypes.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "BSAnimNotify.generated.h"



UCLASS()
class BASICSHOOTER_API UBSAnimNotify : public UAnimNotify
{
	GENERATED_BODY()
public:
	FOnNotifiedSignature OnNotifiedSignature;
	
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
