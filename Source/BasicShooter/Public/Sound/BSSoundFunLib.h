// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BSSoundFunLib.generated.h"

class USoundClass;


UCLASS()
class BASICSHOOTER_API UBSSoundFunLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	static bool SetSoundClassVolume(USoundClass* SoundClass, float Volume);

	UFUNCTION(BlueprintCallable)
	static bool ToggleSoundClassVolume(USoundClass* SoundClass);
};
