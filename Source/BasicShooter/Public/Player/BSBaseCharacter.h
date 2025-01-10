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

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	UInputAction* JumpAction;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	UInputAction* RunAction;
};

UCLASS()
class BASICSHOOTER_API ABSBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABSBaseCharacter(const FObjectInitializer& ObjInit);

	UFUNCTION(BlueprintCallable,Category = "Movement")
	bool IsRunning();
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
	bool isRunningState;

private:
	void EnhancedInputMove(const FInputActionValue& Value);
	void EnhancedInputLook(const FInputActionValue& Value);
	void OnStartRun(const FInputActionValue& Value);
	void OnEndRun(const FInputActionValue& Value);

};
