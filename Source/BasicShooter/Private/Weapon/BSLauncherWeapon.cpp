// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon/BSLauncherWeapon.h"

#include "Kismet/GameplayStatics.h"

void ABSLauncherWeapon::MakeShot()
{
	if (!GetWorld() || IsAmmoEmpty())
	{
		return;
	}

	FVector TraceStart, TraceEnd;
	if (!GetTraceData(TraceStart, TraceEnd))
	{
		return;
	}
	FHitResult HitResult;
	MakeHit(HitResult, TraceStart, TraceEnd);

	const FVector EndPoint = HitResult.bBlockingHit ? HitResult.ImpactPoint : TraceEnd;
	const FVector Direction = (EndPoint - GetMuzzleWorldLocation().GetSafeNormal());

	const FTransform SpawnTransform(FRotator::ZeroRotator, GetMuzzleWorldLocation());
	if (auto Projectile = GetWorld()->SpawnActorDeferred<ABSProjectile>(ProjectileClass, SpawnTransform))
	{
		Projectile->SetShotDirection(Direction);
		Projectile->SetOwner(GetOwner());
		Projectile->FinishSpawning(SpawnTransform);
	}
	SpawnTraceFX(GetMuzzleWorldLocation(),EndPoint);
	DecreaseAmmo();
	SpawnMuzzleFX();
}