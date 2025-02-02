// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/BSBasePickup.h"

#include "BSCoreUtils.h"
#include "Components/BSHealthComponent.h"
#include "GameFramework/Character.h"

DEFINE_LOG_CATEGORY_STATIC(LogBasePickup, All, All);

ABSBasePickup::ABSBasePickup()
{
	PrimaryActorTick.bCanEverTick = true;
	
	CollisionComponent = CreateDefaultSubobject<USphereComponent>("CollisionComponent");
	CollisionComponent->IgnoreActorWhenMoving(GetOwner(),true);
	CollisionComponent->InitSphereRadius(50.0f);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndProbe);
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

	SetRootComponent(CollisionComponent);

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
	MeshComponent->SetupAttachment(GetRootComponent());
}

void ABSBasePickup::BeginPlay()
{
	Super::BeginPlay();
	
}
void ABSBasePickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	const auto PlayerPawn = Cast<APawn>(OtherActor);
	if (!PlayerPawn)
	{
		return;
	}
	if (!PickUpTo(PlayerPawn))
	{
		return;
	}
	OnPickupTakenSignature.Broadcast();
	UE_LOG(LogBasePickup, Display, TEXT("Pickup was taken"));
}
bool ABSBasePickup::PickUpTo(APawn* PlayerPawn)
{
	return false;
}

void ABSBasePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

