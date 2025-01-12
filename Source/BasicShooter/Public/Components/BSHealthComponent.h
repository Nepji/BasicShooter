// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BSHealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeath)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChange,float)

USTRUCT(Blueprintable)
struct FHealthData
{
	GENERATED_BODY()


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool Curable = true;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool AutoHeal = false;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = 0.0f))
	float HealDelay = 3.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = 0.1f))
	float HealRate = 3.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = 0.0f))
	float HealingValue = 1.0f;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BASICSHOOTER_API UBSHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	FOnDeath OnDeath;
	FOnHealthChange OnHealthChange;

public:	
	UBSHealthComponent();

	UFUNCTION(Blueprintable)
	const float GetHealth();

	UFUNCTION(Blueprintable)
	const bool IsDead();

	UFUNCTION(Blueprintable)
	void setHealth(float Health);

protected:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = 0.0f))
	float MaxHealth = 100.0f;
	
	UPROPERTY(EditDefaultsOnly,Blueprintable)
	FHealthData HealthData;

protected:
	virtual void BeginPlay() override;


private:
	float Health = 0.0f;
	FTimerHandle HealTimerHandle;
private:
	UFUNCTION(Blueprintable)
	void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
	void HealUpdate();
	
};
