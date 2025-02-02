// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/BSPickupHUB.h"

ABSPickupHUB::ABSPickupHUB()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ABSPickupHUB::BeginPlay()
{
	Super::BeginPlay();

	SpawnPickup();
}

void ABSPickupHUB::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
void ABSPickupHUB::SpawnPickup()
{
	if (Pickups.IsEmpty())
	{
		return;
	}

	const FTransform SpawnTransform(FRotator::ZeroRotator, GetActorLocation());
	CurrentPickup = GetWorld()->SpawnActorDeferred<ABSBasePickup>(Pickups[CurrentPickupIndex], SpawnTransform);
	if (CurrentPickup)
	{
		CurrentPickup->SetOwner(this);
		CurrentPickup->FinishSpawning(SpawnTransform);
		CurrentPickup->OnPickupTakenSignature.AddUObject(this,&ABSPickupHUB::OnPickupTaken);
	}
}
void ABSPickupHUB::OnPickupTaken()
{
	GetWorld()->GetTimerManager().SetTimer(PickupRespawnTimerHandle,this,&ABSPickupHUB::SpawnPickup,RespawnRate,false);
	CurrentPickupIndex = (CurrentPickupIndex + 1) % Pickups.Num();
	CurrentPickup->Destroy();

}

