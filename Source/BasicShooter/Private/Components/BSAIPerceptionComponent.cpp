// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/BSAIPerceptionComponent.h"

#include "AIController.h"
#include "BSCoreUtils.h"
#include "Components/BSHealthComponent.h"
#include "Perception/AISense_Sight.h"

AActor* UBSAIPerceptionComponent::GetClosestEnemy()
{
	TArray<AActor*> PercieveActors;
	GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(),PercieveActors);
	if(PercieveActors.IsEmpty())
	{
		return nullptr;
	}

	const auto Controller = Cast<AAIController>(GetOwner());
	if(!Controller)
	{
		return nullptr;
	}

	const auto Pawn = Controller->GetPawn();
	if(!Pawn)
	{
		return nullptr;
	}
	float BestDistance = MAX_FLT;
	AActor* BestPawn = nullptr;
	for(const auto PerceiveActor : PercieveActors)
	{
		const auto HealthComponent = PerceiveActor->GetComponentByClass<UBSHealthComponent>();

		const auto PerceivePawn = Cast<APawn>(PerceiveActor);
		const auto AreEnemies = PerceivePawn && BSCoreUtils::AreEnemies(Controller, PerceivePawn->Controller);
		
		if(HealthComponent && !HealthComponent->IsDead() && AreEnemies)
		{
			const float CurrentDistance = (PerceiveActor->GetActorLocation() - Pawn->GetActorLocation()).Size();
			if(CurrentDistance < BestDistance)
			{
				BestPawn = PerceiveActor;
				BestDistance = CurrentDistance;
			}
		}
	}
	return BestPawn;
}