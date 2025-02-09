// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BSCoreTypes.h"
#include "Components/ActorComponent.h"
#include "Templates/Tuple.h"
#include "BSHealthComponent.generated.h"




class UCameraShakeBase;


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
	float GetHealth();

	UFUNCTION(Blueprintable,BlueprintCallable, Category = "Health")
	bool IsDead();

	UFUNCTION(Blueprintable,BlueprintCallable, Category = "Health")
	void setHealth(float Health);

	UFUNCTION(Blueprintable, BlueprintCallable, Category = "Health")
	float GetHealthPercent() const;

	UFUNCTION(Blueprintable, BlueprintCallable, Category = "Health")
	bool TryAddHealth(int32 AmountOfHealth);

protected:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = 0.0f),Category = "Health")
	float MaxHealth = 100.0f;
	
	UPROPERTY(EditDefaultsOnly,Blueprintable,Category = "Health")
	FHealthData HealthData;

	UPROPERTY(EditDefaultsOnly,Blueprintable, Category = "VFX")
	TSubclassOf<UCameraShakeBase> CameraShake;

protected:
	virtual void BeginPlay() override;


private:
	float Health = 0.0f;
	FTimerHandle HealTimerHandle;
	UPROPERTY()
	TMap<AActor*,float> DamageCausers; //Who and Amount
private:
	void AddDamageLog(AController* Damager, float Damage);
	UFUNCTION(Blueprintable)
	void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
	void HealUpdate();
	bool HealthIsFull() const;
	void PlayCameraShake();
	void Killed(AController* KillerController, const AActor* DamageCauser);
	AController* HasKillAssistant(const AController* KillerController); 
	
};
