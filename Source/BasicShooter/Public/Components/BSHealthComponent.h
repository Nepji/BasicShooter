// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BSCoreTypes.h"
#include "Components/ActorComponent.h"
#include "BSHealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeath)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChange,float)



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BASICSHOOTER_API UBSHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	FOnDeath OnDeath;
	FOnHealthChange OnHealthChange;

public:	
	UBSHealthComponent();

	UFUNCTION(Blueprintable,BlueprintCallable, Category = "Health")
	const float GetHealth();

	UFUNCTION(Blueprintable,BlueprintCallable, Category = "Health")
	const bool IsDead();

	UFUNCTION(Blueprintable,BlueprintCallable, Category = "Health")
	void setHealth(float Health);

	UFUNCTION(Blueprintable,BlueprintCallable, Category = "Health")
	float GetHealthPercent() const;
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
