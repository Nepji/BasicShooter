// Fill out your copyright notice in the Description page of Project Settings.

#include "Sound/BSSoundFunLib.h"

#include "Sound/SoundClass.h"
bool UBSSoundFunLib::SetSoundClassVolume(USoundClass* SoundClass, float Volume)
{
	if (!SoundClass)
	{
		return false;
	}
	SoundClass->Properties.Volume = FMath::Clamp(Volume, 0.0f, 1.0f);
	return true;
}
bool UBSSoundFunLib::ToggleSoundClassVolume(USoundClass* SoundClass)
{
	if(!SoundClass)
	{
		return false;
	}
	const auto NextVolume = SoundClass->Properties.Volume > 0.0f ? 0.0f : 1.0f;
	return SetSoundClassVolume(SoundClass,NextVolume);
}