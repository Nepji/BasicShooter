// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/BSWeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/DecalComponent.h"
#include "Kismet/GameplayStatics.h"

UBSWeaponFXComponent::UBSWeaponFXComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}
void UBSWeaponFXComponent::PlayImpactFX(const FHitResult& HitResult)
{
	auto ImpactData = DefaultImpactData;

	if (HitResult.PhysMaterial.IsValid())
	{
		const auto PhysMat = HitResult.PhysMaterial.Get();
		if (ImpactDataMap.Contains(PhysMat))
		{
			ImpactData = ImpactDataMap[PhysMat];
		}
	}

	// Niagara
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(
		GetWorld(),
		ImpactData.NiagaraEffect,
		HitResult.ImpactPoint,
		HitResult.ImpactNormal.Rotation());

	// Decal
	const auto DecalComponent = UGameplayStatics::SpawnDecalAtLocation(
		GetWorld(),
		ImpactData.DecalData.Material,
		ImpactData.DecalData.Size,
		HitResult.ImpactPoint,
		HitResult.ImpactNormal.Rotation());

	if(DecalComponent)
	{
		DecalComponent->SetFadeOut(ImpactData.DecalData.LifeTime,ImpactData.DecalData.FadeOutTime);
	}
}
