// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BSCoreTypes.h"
#include "GameFramework/Character.h"
#include "BSBaseCharacter.generated.h"

class UBSHealthComponent;
class UBSWeaponComponent;

UCLASS()
class BASICSHOOTER_API ABSBaseCharacter : public ACharacter
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly,Blueprintable, Category = "Health")
	float ToDestroyTimer = 5.0;
public:
	ABSBaseCharacter(const FObjectInitializer& ObjInit);
	virtual void Tick(float DeltaTime) override;
	void SetPlayerColor(FLinearColor Color) const;
	
	UFUNCTION(BlueprintCallable,Category = "Movement")
	bool IsRunning();

	UFUNCTION(BlueprintCallable, Category = "Movement")
	float GetDirection();


protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	UBSHealthComponent* HealthComponent;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	UBSWeaponComponent* WeaponComponent;

	UPROPERTY(EditDefaultsOnly,Blueprintable, Category = "Animation")
	UAnimMontage* DeathAnimMontage;	

	UPROPERTY(EditDefaultsOnly,Blueprintable, Category = "Material")
	FName MaterialColorName = "Color"; 

protected:
	bool isRunningState;
protected:
	virtual void BeginPlay() override;
	virtual void OnDeath();
	

};
