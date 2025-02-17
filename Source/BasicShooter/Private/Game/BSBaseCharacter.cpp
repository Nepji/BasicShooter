// Fill out your copyright notice in the Description page of Project Settings.

#include "BSBaseCharacter.h"

#include "Engine/LocalPlayer.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/BSHealthComponent.h"
#include "Components/BSMovementComponent.h"
#include "Components/BSWeaponComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

ABSBaseCharacter::ABSBaseCharacter(const FObjectInitializer& ObjInit)
	: Super(ObjInit.SetDefaultSubobjectClass<UBSMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = true;

	HealthComponent = CreateDefaultSubobject<UBSHealthComponent>("HealthComponent");
	WeaponComponent = CreateDefaultSubobject<UBSWeaponComponent>("WeaponComponent");
}
bool ABSBaseCharacter::IsRunning()
{
	return isRunningState;
}

float ABSBaseCharacter::GetDirection()
{
	if (GetVelocity().IsZero())
	{
		return 0.0f;
	}
	const auto VelocityNormal = GetVelocity().GetSafeNormal();
	const float AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));
	const auto CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);
	const float Degrees = FMath::RadiansToDegrees(AngleBetween);

	return CrossProduct.IsZero() ? Degrees : Degrees * FMath::Sign(CrossProduct.Z);
}

void ABSBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(GetMesh());
	check(HealthComponent);
	check(WeaponComponent);
	HealthComponent->OnDeath.AddUObject(this, &ABSBaseCharacter::OnDeath);
}

void ABSBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void ABSBaseCharacter::SetPlayerColor(FLinearColor Color) const
{
	const auto MaterialInst = GetMesh()->CreateAndSetMaterialInstanceDynamic(0);
	if(!MaterialInst)
	{
		return;
	}
	MaterialInst->SetVectorParameterValue(MaterialColorName,Color);
}



void ABSBaseCharacter::OnDeath()
{
	UGameplayStatics::SpawnSoundAtLocation(GetWorld(),DeathSound,GetActorLocation());
	GetCharacterMovement()->DisableMovement();
	SetLifeSpan(ToDestroyTimer);
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Ignore);
	
	WeaponComponent->StopFire();

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->SetSimulatePhysics(true); 
}
