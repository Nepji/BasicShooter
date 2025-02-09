// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/BSMovementComponent.h"

#include "BSBaseCharacter.h"

float UBSMovementComponent::GetMaxSpeed() const
{
	const float MaxSpeed = Super::GetMaxSpeed(); 

	ABSBaseCharacter* Player = Cast<ABSBaseCharacter>(GetPawnOwner());
	
	return Player && Player->IsRunning() ? MaxSpeed * RunModifier: MaxSpeed;
}