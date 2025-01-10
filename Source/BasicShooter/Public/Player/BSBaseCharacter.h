// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputSubsystemInterface.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Character.h"
#include "BSBaseCharacter.generated.h"


USTRUCT(Blueprintable)
struct FInputData
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	UInputMappingContext* MappingContext;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	UInputAction* MoveAction;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	UInputAction* LookAround;
};

UCLASS()
class BASICSHOOTER_API ABSBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABSBaseCharacter();
protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	UCameraComponent* CameraComponent;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	USpringArmComponent* SpringArmComponent;
	

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category = "Input Data")
	FInputData InputData;

	
protected:
	virtual void BeginPlay() override;
	


public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


private:
	void EnhancedInputMove(const FInputActionValue& Value);
	void EnhancedInputLook(const FInputActionValue& Value);

};
