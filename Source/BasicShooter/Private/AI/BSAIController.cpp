// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BSAIController.h"
#include "AI/BSAICharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

ABSAIController:: ABSAIController()
{
	PrimaryActorTick.bCanEverTick = true;
	AIPerceptionComponent = CreateDefaultSubobject<UBSAIPerceptionComponent>("BSPerceptionComponent");
	SetPerceptionComponent(*AIPerceptionComponent);
}
void ABSAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (const auto AICharacter = Cast<ABSAICharacter>(InPawn))
	{
		RunBehaviorTree(AICharacter->BehaviorTreeAsset);
	}
}
void ABSAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	const auto GetClosestEnemy = AIPerceptionComponent->GetClosestEnemy();
	SetFocus(GetClosestEnemy);
}
AActor* ABSAIController::GetFocusedOnActor() const
{
	if (!GetBlackboardComponent())
	{
		return nullptr;
	}
	return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(FocusOnKeyName));
}
bool ABSAIController::IsLookTowardsEnemy(const float Threshold = 0.75f) const
{
	const auto Enemy = GetFocusedOnActor();
	if(!Enemy)
	{
		return false;
	}

	const auto ForwardVector = GetPawn()->GetActorForwardVector();
	const auto DirectionToTarget = (Enemy->GetActorLocation() - GetPawn()->GetActorLocation()).GetSafeNormal();
	
	const float Dot = FVector::DotProduct(ForwardVector, DirectionToTarget);
	
	return Dot >= Threshold; 
	
}