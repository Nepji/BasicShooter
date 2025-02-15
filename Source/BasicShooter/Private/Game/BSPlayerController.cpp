// Fill out your copyright notice in the Description page of Project Settings.

#include "BSPlayerController.h"

#include "BSCoreTypes.h"
#include "BSGameModeBase.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/BSRespawnComponent.h"
#include "GameFramework/GameModeBase.h"

ABSPlayerController::ABSPlayerController()
{
	RespawnComponent = CreateDefaultSubobject<UBSRespawnComponent>("RespawnComponents");
}
void ABSPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = 
			   ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(MappingContext, 0);
	}

	if(GetWorld())
	{
		const auto GameMode = Cast<ABSGameModeBase>(GetWorld()->GetAuthGameMode());
		if(GameMode)
		{
			GameMode->OnMatchStateChanged.AddUObject(this, &ABSPlayerController::OnMatchStateChanged);
		}
	}
}
void ABSPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	OnNewPawn.Broadcast(InPawn);
}
void ABSPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Triggered, this, &ABSPlayerController::EnhancedInputPause);
	}
}
void ABSPlayerController::EnhancedInputPause()
{
	if (!GetWorld() || !GetWorld()->GetAuthGameMode())
	{
		return;
	}
	GetWorld()->GetAuthGameMode()->SetPause(this);
}
void ABSPlayerController::OnMatchStateChanged(EBSMatchState State)
{
	if(State == EBSMatchState::Pause || State == EBSMatchState::GameOver)
	{
		SetInputMode(FInputModeUIOnly());
		bShowMouseCursor = true;
	}
	else if(State == EBSMatchState::InProgress || State == EBSMatchState::WaitingToStart)
	{
		SetInputMode(FInputModeGameOnly());
		bShowMouseCursor = false;
	}
}