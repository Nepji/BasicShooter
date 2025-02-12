// Fill out your copyright notice in the Description page of Project Settings.


#include "Level/Decorations/BSGroundEntity.h"

ABSGroundEntity::ABSGroundEntity()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>("CollisionComponent");
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	SetRootComponent(CollisionComponent);

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
	MeshComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	MeshComponent->SetupAttachment(GetRootComponent());
}
void ABSGroundEntity::OnRoundBegin()
{
	if(!GetWorld())
	{
		return;
	}
	TimerCountDown = FadeTime;
	CollisionComponent->SetVisibility(true);
	GetWorld()->GetTimerManager().SetTimer(FEntityFadeTimerHandle,this, &ABSGroundEntity::TimerUpdate,1.0f,true);
}

void ABSGroundEntity::BeginPlay()
{
	Super::BeginPlay();

	check(CollisionComponent);
	check(MeshComponent);
}
void ABSGroundEntity::TimerUpdate()
{
	if(!GetWorld())
	{
		return;
	}
	if( --TimerCountDown > 0)
	{
		return;
	}
	GetWorld()->GetTimerManager().ClearTimer(FEntityFadeTimerHandle);
	CollisionComponent->SetVisibility(false);
}


