// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BSAICharacter.h"

#include "AI/BSAIController.h"
#include "Components/AI/BSAIWeaponComponent.h"

ABSAICharacter::ABSAICharacter(const FObjectInitializer& OnjInit)
	: Super(OnjInit.SetDefaultSubobjectClass<UBSAIWeaponComponent>("WeaponComponent"))
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = ABSAIController::StaticClass();
}
void ABSAICharacter::OnDeath()
{
	Super::OnDeath();
	const auto AIController = Cast<AAIController>(Controller);
	if(AIController || AIController->BrainComponent)
	{
		AIController->BrainComponent->Cleanup();
	}
}