// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputSubsystemInterface.h"
#include "Camera/CameraComponent.h"
#include "Components/BSHealthComponent.h"
#include "Components/TextRenderComponent.h"
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
	UPROPERTY(EditDefaultsOnly,Blueprintable, Category = "Health")
	float ToDeathTimer = 5.0;

public:
	ABSBaseCharacter(const FObjectInitializer& ObjInit);

	UFUNCTION(BlueprintCallable,Category = "Movement")
	bool IsRunning();

	UFUNCTION(BlueprintCallable,Category = "Movement")
	const float GetDirection();

protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	UCameraComponent* CameraComponent;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	UBSHealthComponent* HealthComponent;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	UTextRenderComponent* HealthTextRenderComponent;

	UPROPERTY(EditDefaultsOnly,Blueprintable, Category = "Animation")
	UAnimMontage* DeathAnimMontage;	

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
	void OnDeath();
	void OnHealthChange(float Health);

};
