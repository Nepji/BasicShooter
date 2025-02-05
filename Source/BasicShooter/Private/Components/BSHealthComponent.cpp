
#include "Components/BSHealthComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All);

UBSHealthComponent::UBSHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}
const float UBSHealthComponent::GetHealth()
{
	return Health;
}
const bool UBSHealthComponent::IsDead()
{
	return (Health <= 0);
}

// Called when the game starts
void UBSHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	checkf(MaxHealth > 0, TEXT("MaxHealth cannot be less or equel zero"));
	setHealth(MaxHealth);
	if (AActor* ComponentOwner = GetOwner())
	{
		ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &UBSHealthComponent::OnTakeAnyDamage);
	}
}
void UBSHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage == 0 || IsDead() || !GetWorld())
	{
		return;
	}
	UE_LOG(LogHealthComponent, Display, TEXT("Recieved Damage: by %s, amount %.2f"), *DamagedActor->GetName(), Damage);
	GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
	// Incoming Damage can heal, but character can be inCurable
	setHealth(Health - (HealthData.Curable ? Damage : FMath::Abs(Damage)));

	if (IsDead())
	{
		OnDeath.Broadcast();
	}
	else if (HealthData.AutoHeal)
	{
		GetWorld()->GetTimerManager().SetTimer(HealTimerHandle, this, &UBSHealthComponent::HealUpdate, HealthData.HealRate, true, HealthData.HealDelay);
	}

	PlayCameraShake();
}

void UBSHealthComponent::HealUpdate()
{
	setHealth(Health + HealthData.HealingValue);

	if (Health == MaxHealth)
	{
		GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
	}
}
bool UBSHealthComponent::HealthIsFull() const
{
	if (Health == MaxHealth)
	{
		return true;
	}
	return false;
}
void UBSHealthComponent::PlayCameraShake()
{
	if (IsDead())
	{
		return;
	}
	const auto Player = Cast<APawn>(GetOwner());
	if(!Player)
	{
		return;
	}
	const auto Controller = Player->GetController<APlayerController>();
	if(!Controller || !Controller->PlayerCameraManager)
	{
		return;
	}
	Controller->PlayerCameraManager->StartCameraShake(CameraShake);
}

void UBSHealthComponent::setHealth(float NewHealth)
{
	const auto NextHealth = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
	const auto HealthDelta = Health-NextHealth;
	Health = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
	OnHealthChange.Broadcast(Health,HealthDelta);
}
float UBSHealthComponent::GetHealthPercent() const
{
	return Health / MaxHealth;
}
bool UBSHealthComponent::TryAddHealth(int32 AmountOfHealth)
{
	if (IsDead() || HealthIsFull())
	{
		return false;
	}
	const float NewHealth = Health + AmountOfHealth;
	setHealth(NewHealth);
	return true;
}
