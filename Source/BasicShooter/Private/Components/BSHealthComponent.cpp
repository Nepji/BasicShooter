
#include "Components/BSHealthComponent.h"

#include "BSGameModeBase.h"
#include "GameFramework/Character.h"
#include "Perception/AISense_Damage.h"
#include "Perception/AISense_Hearing.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All);

UBSHealthComponent::UBSHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}
float UBSHealthComponent::GetHealth()
{
	return Health;
}
bool UBSHealthComponent::IsDead()
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
		ComponentOwner->OnTakePointDamage.AddDynamic(this, &UBSHealthComponent::OnTakePointDamage);
		ComponentOwner->OnTakeRadialDamage.AddDynamic(this, &UBSHealthComponent::OnTakeRadialDamage);
	}
}
void UBSHealthComponent::AddDamageLog(AController* Damager, float Damage)
{
	if (DamageCausers.Contains(Damager))
	{
		const auto Record = DamageCausers.Find(Damager);
		*Record += Damage;
		return;
	}
	DamageCausers.Add(Damager, Damage);
}
void UBSHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	ApplyDamage(Damage, InstigatedBy);
}
void UBSHealthComponent::OnTakePointDamage(AActor* DamagedActor, float Damage, AController* InstigatedBy, FVector HitLocation, UPrimitiveComponent* FHitComponent, FName BoneName, FVector ShotFromDirection, const UDamageType* DamageType, AActor* DamageCauser)
{
	const auto FinalDamage = Damage * GetPointDamageModifier(DamagedActor, BoneName);
	ApplyDamage(FinalDamage, InstigatedBy);
}
void UBSHealthComponent::OnTakeRadialDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, FVector Origin, const FHitResult&, AController* InstigatedBy, AActor* DamageCauser)
{
	ApplyDamage(Damage, InstigatedBy);
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
	if (!Player)
	{
		return;
	}
	const auto Controller = Player->GetController<APlayerController>();
	if (!Controller || !Controller->PlayerCameraManager)
	{
		return;
	}
	Controller->PlayerCameraManager->StartCameraShake(CameraShake);
}
void UBSHealthComponent::Killed(AController* KillerController, const AActor* DamageCauser)
{
	if (!GetWorld())
	{
		return;
	}
	const auto GameMode = Cast<ABSGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode)
	{
		return;
	}
	const auto Player = Cast<APawn>(GetOwner());
	const auto VictimController = Player ? Player->Controller : nullptr;

	if (const auto AssistantController = HasKillAssistant(KillerController))
	{
		GameMode->Killed(KillerController, VictimController, AssistantController);
	}
	else
	{
		GameMode->Killed(KillerController, VictimController);
	}

	UE_LOG(LogHealthComponent, Display, TEXT("Lethal demage recieved: %s / from %s / using %s weapon"), *GetOwner()->GetName(), *KillerController->GetName(), *DamageCauser->GetName());
}
AController* UBSHealthComponent::HasKillAssistant(const AController* KillerController)
{
	if (!IsDead() || DamageCausers.IsEmpty())
	{
		return nullptr;
	}
	DamageCausers.ValueSort([](const float& A, const float& B) {
		return A > B;
	});
	const auto MostDamageCauserIterator = DamageCausers.CreateConstIterator();
	if (!MostDamageCauserIterator)
	{
		return nullptr;
	}
	const auto AssistantController = Cast<AController>(MostDamageCauserIterator->Key);
	return AssistantController != KillerController ? AssistantController : nullptr;
}
void UBSHealthComponent::ApplyDamage(float Damage, AController* InstigatedBy)
{
	if (Damage == 0 || IsDead() || !GetWorld())
	{
		return;
	}

	AddDamageLog(InstigatedBy, Damage);
	UE_LOG(LogHealthComponent, Display, TEXT("Recieved Damage: %s, amount %.2f"), *GetOwner()->GetName(), Damage);
	GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
	// Incoming Damage can heal, but character can be inCurable
	setHealth(Health - (HealthData.Curable ? Damage : FMath::Abs(Damage)));

	if (IsDead())
	{
		Killed(InstigatedBy, InstigatedBy->GetPawn());
		OnDeath.Broadcast();
	}
	else if (HealthData.AutoHeal)
	{
		GetWorld()->GetTimerManager().SetTimer(HealTimerHandle, this, &UBSHealthComponent::HealUpdate, HealthData.HealRate, true, HealthData.HealDelay);
	}

	PlayCameraShake();
	ReportDamageEvent(Damage, InstigatedBy);
}
float UBSHealthComponent::GetPointDamageModifier(AActor* DamagedActor, const FName& BoneName)
{
	const auto Character = Cast<ACharacter>(DamagedActor);
	if (!Character || !Character->GetMesh() || !Character->GetMesh()->GetBodyInstance(BoneName))
	{
		return 1.0f;
	}

	const auto PhysMaterial = Character->GetMesh()->GetBodyInstance(BoneName)->GetSimplePhysicalMaterial();
	if (!PhysMaterial || !DamageModifiers.Contains(PhysMaterial))
	{
		return 1.0f;
	}
	return DamageModifiers[PhysMaterial];
}
void UBSHealthComponent::ReportDamageEvent(float Damage, AController* InstigatedBy)
{
	if(!InstigatedBy || !InstigatedBy->GetPawn() || !GetOwner())
	{
		return;
	}
	
	UAISense_Damage::ReportDamageEvent(						 //
		GetWorld(),											 //
		GetOwner(),											 //
		InstigatedBy->GetPawn(),							 //
		Damage, InstigatedBy->GetPawn()->GetActorLocation(), //
		GetOwner()->GetActorLocation());
}

void UBSHealthComponent::setHealth(float NewHealth)
{
	const auto NextHealth = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
	const auto HealthDelta = Health - NextHealth;
	Health = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
	OnHealthChange.Broadcast(Health, HealthDelta);
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
