// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BSRespawnComponent.h"
#include "GameFramework/PlayerController.h"
#include "BSPlayerController.generated.h"

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
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	UBSRespawnComponent* RespawnComponent;

protected:
	virtual void OnPossess(APawn* InPawn) override;
};
