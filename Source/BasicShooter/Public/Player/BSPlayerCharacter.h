// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BSBaseCharacter.h"
#include "BSPlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class USphereComponent;

UCLASS()
class BASICSHOOTER_API ABSPlayerCharacter : public ABSBaseCharacter
{
	GENERATED_BODY()

public:
	ABSPlayerCharacter(const FObjectInitializer& ObjInit);
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	UCameraComponent* CameraComponent;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	USphereComponent* CameraCollisionComponent;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	USpringArmComponent* SpringArmComponent;
protected:
	UFUNCTION()
	void OnCameraCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnCameraCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	virtual void BeginPlay() override;
	virtual void OnDeath() override;

private:
	void EnhancedInputMove(const FInputActionValue& Value);
	void EnhancedInputLook(const FInputActionValue& Value);
	
	void OnStartRun(const FInputActionValue& Value);
	void OnEndRun(const FInputActionValue& Value);

	void CheckCameraOverlap() const;
};
