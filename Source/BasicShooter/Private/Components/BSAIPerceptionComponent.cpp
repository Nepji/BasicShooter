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
	for(const auto PercieveActor : PercieveActors)
	{
		const auto HealthComponent = PercieveActor->GetComponentByClass<UBSHealthComponent>();
		if(HealthComponent && !HealthComponent->IsDead())
		{
			const float CurrentDistance = (PercieveActor->GetActorLocation() - Pawn->GetActorLocation()).Size();
			if(CurrentDistance < BestDistance)
			{
				BestPawn = PercieveActor;
				BestDistance = CurrentDistance;
			}
		}
	}
	return BestPawn;
}