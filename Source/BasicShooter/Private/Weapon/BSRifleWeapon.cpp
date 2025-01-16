// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/BSRifleWeapon.h"

#include "Kismet/GameplayStatics.h"

void ABSRifleWeapon::StartFire()
{
	MakeShot();
	GetWorldTimerManager().SetTimer(ShotTimerHandle,this,&ABSBaseWeapon::MakeShot,FireRate,true);
}
void ABSRifleWeapon::StopFire()
{
	GetWorldTimerManager().ClearTimer(ShotTimerHandle);
}

void ABSRifleWeapon::MakeShot()
{
	if(!GetWorld())
	{
		return;
	}
	
	FVector TraceStart,TraceEnd;
	if(!GetTraceData(TraceStart,TraceEnd))
	{
		return;
	}

	FHitResult HitResult;
	MakeHit(HitResult,TraceStart,TraceEnd);

	if(HitResult.bBlockingHit)
	{
		if(AActor* Enemy = Cast<AActor>(HitResult.GetActor()))
		{
			UGameplayStatics::ApplyPointDamage(Enemy,Damage,TraceStart,HitResult,GetPlayerController(),GetOwner(),nullptr);
		
		}
		DrawDebugLine(GetWorld(),GetMuzzleWorldLocation(),HitResult.ImpactPoint,FColor::Red,false,2.0f);
		DrawDebugSphere(GetWorld(),HitResult.ImpactPoint,10,24,FColor::Red,false,3.0f);
	}
	else
	{
		DrawDebugLine(GetWorld(),GetMuzzleWorldLocation(),TraceEnd,FColor::Red,false,2.0f);
	}
}

