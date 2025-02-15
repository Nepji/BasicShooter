// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BSCoreTypes.h"
#include "Components/BSRespawnComponent.h"
#include "GameFramework/PlayerController.h"
#include "BSPlayerController.generated.h"

class UInputAction;
class UInputMappingContext;
/**
 *
 */
UCLASS()
class BASICSHOOTER_API ABSPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ABSPlayerController();
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input")
	// ReSharper disable once UnrealHeaderToolError
	UInputMappingContext* MappingContext;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "Input")
	UInputAction* PauseAction;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UBSRespawnComponent* RespawnComponent;


protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void SetupInputComponent() override;

private:
	void EnhancedInputPause();
	void OnMatchStateChanged(EBSMatchState State);
};
