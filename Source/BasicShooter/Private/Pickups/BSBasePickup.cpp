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
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComponent->SetupAttachment(GetRootComponent());
}

void ABSBasePickup::BeginPlay()
{
	Super::BeginPlay();
	GenerateRotationYaw();
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
	AddActorLocalRotation(FRotator(0.0f, RotationYaw, 0.0f));
}
void ABSBasePickup::GenerateRotationYaw()
{
	const auto Direction = FMath::RandBool() ? 1.0f : -1.0f;
	RotationYaw = FMath::RandRange(1.0f,2.0f) * Direction;
}

