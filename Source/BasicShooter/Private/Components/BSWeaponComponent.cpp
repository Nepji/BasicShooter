

#include "Components/BSWeaponComponent.h"

#include "BSBaseCharacter.h"
#include "Animation/Notify/BSEquipFinishedNotify.h"
#include "..\..\Public\Animation\Notify\BSReloadFinishedAnimNotify.h"
#include "Animation/AnimUtils.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Weapon/BSBaseWeapon.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeaponComponent, All, All)

constexpr static int32 WeaponMaxNum = 2;

UBSWeaponComponent::UBSWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UBSWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	checkf(WeaponData.Num() <= WeaponMaxNum && WeaponData.Num(), TEXT("Those character can hold up to &i weapon items"),WeaponMaxNum);
	SpawnWeapon();
	EquipWeapon(CurrentWeaponIndex);
	InitAnimations();
}


void UBSWeaponComponent::AttachWeaponToSocket(ABSBaseWeapon* Weapon, USkeletalMeshComponent* SceneComponent, FName SocketName)
{
	const FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	Weapon->AttachToComponent(SceneComponent, AttachmentRules, SocketName);
}
void UBSWeaponComponent::EquipWeapon(int32 WeaponIndex)
{
	if (Weapons.IsEmpty() || !FMath::IsWithinInclusive(WeaponIndex, 0, Weapons.Num()))
	{
		return;
	}
	if (const ACharacter* Character = Cast<ACharacter>(GetOwner()))
	{
		if (CurrentWeapon)
		{
			CurrentWeapon->StopFire();
			AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), CurrentWeaponSocket(CurrentWeapon->GetClass()));
		}
		CurrentWeapon = Weapons[WeaponIndex];
		CurrentReloadAnimation = WeaponData.FindByPredicate(
											   [&](const FWeaponData& Data) {
												   return Data.WeaponClass == CurrentWeapon->GetClass();
											   })
									 ->ReloadAnimation;
		AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponAttachSocket);
		EquipAnimationInProgress = true;
		PlayAnimMontage(EquipAnimMontage);
	}
}
void UBSWeaponComponent::SpawnWeapon()
{
	if (!GetWorld())
	{
		return;
	}
	for (auto OneWeaponData : WeaponData)
	{
		if (auto Weapon = GetWorld()->SpawnActor<ABSBaseWeapon>(OneWeaponData.WeaponClass))
		{
			ACharacter* Character = Cast<ACharacter>(GetOwner());
			if (!Character)
			{
				continue;
			}
			Weapon->OnClipEmptySignature.AddUObject(this, &UBSWeaponComponent::OnEmptyClip);
			Weapon->SetOwner(Character);
			Weapons.Add(Weapon);

			AttachWeaponToSocket(Weapon, Character->GetMesh(), CurrentWeaponSocket(GetClass()));
		}
	}
}

FName UBSWeaponComponent::CurrentWeaponSocket(TSubclassOf<ABSBaseWeapon> WeaponClass) const
{
	return WeaponsToSecondarySlot.Contains(WeaponClass) ? WeaponSecondaryArmorySocket : WeaponArmorySocket;
}
void UBSWeaponComponent::PlayAnimMontage(UAnimMontage* AnimMontage)
{
	if (!AnimMontage)
	{
		return;
	}
	if (ACharacter* Character = Cast<ACharacter>(GetOwner()))
	{
		Character->PlayAnimMontage(AnimMontage);
	}
}
void UBSWeaponComponent::InitAnimations()
{
	if (const auto EquipAnimationFinished = AnimUtils::FindNotifyByClass<UBSEquipFinishedNotify>(EquipAnimMontage))
	{
		EquipAnimationFinished->OnNotifiedSignature.AddUObject(this, &UBSWeaponComponent::OnEquipFinished);
	}
	else
	{
		UE_LOG(LogWeaponComponent, Error, TEXT("AnimNotify %s not found!"), *EquipAnimMontage->GetName());
		checkNoEntry();
	}
	for (const auto OneWeaponData : WeaponData)
	{
		if (const auto ReloadAnimationFinished = AnimUtils::FindNotifyByClass<UBSReloadFinishedAnimNotify>(OneWeaponData.ReloadAnimation))
		{
			ReloadAnimationFinished->OnNotifiedSignature.AddUObject(this, &UBSWeaponComponent::OnReloadFinished);
		}
		else
		{
			if(OneWeaponData.ReloadAnimation != nullptr)
			{
				UE_LOG(LogWeaponComponent,Error,TEXT("AnimNotify \"%s\" for weapon %s not found"),*OneWeaponData.ReloadAnimation->GetName(),*OneWeaponData.WeaponClass->GetName());
			}
			else
			{
				UE_LOG(LogWeaponComponent,Error,TEXT("Reload Animation for weapon %s not found"),*OneWeaponData.WeaponClass->GetName());
			}
			checkNoEntry();
		}
	}

}
void UBSWeaponComponent::OnEquipFinished(USkeletalMeshComponent* MeshComp)
{
	if (const ACharacter* Character = Cast<ACharacter>(GetOwner()))
	{
		if (Character->GetMesh() == MeshComp)
		{
			EquipAnimationInProgress = false;
		}
	}
}
void UBSWeaponComponent::OnReloadFinished(USkeletalMeshComponent* MeshComp)
{
	if (const ACharacter* Character = Cast<ACharacter>(GetOwner()))
	{
		if (Character->GetMesh() == MeshComp)
		{
			ReloadAnimationInProgress = false;
		}
	}
}


void UBSWeaponComponent::StartFire()
{
	if (!CanFire())
	{
		return;
	}
	CurrentWeapon->StartFire();
}

void UBSWeaponComponent::StopFire()
{
	if (!CurrentWeapon)
	{
		return;
	}
	CurrentWeapon->StopFire();
}

void UBSWeaponComponent::NextWeapon()
{
	if (Weapons.IsEmpty())
	{
		return;
	}
	CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
	EquipWeapon(CurrentWeaponIndex);
}
bool UBSWeaponComponent::CanFire() const
{
	const auto Character = Cast<ABSBaseCharacter>(GetOwner());
	const auto MovementComponent = Character->GetMovementComponent();
	return !EquipAnimationInProgress && CurrentWeapon && !Character->IsRunning() && !MovementComponent->IsFalling() && !ReloadAnimationInProgress;
}
bool UBSWeaponComponent::CanReload() const
{
	return !ReloadAnimationInProgress && !CurrentWeapon->CanReload();
}

void UBSWeaponComponent::OnEmptyClip()
{
	ChangeClip();
}

void UBSWeaponComponent::Reload()
{
	ChangeClip();
}
void UBSWeaponComponent::ChangeClip()
{
	if (!CanReload())
	{
		return;
	}
	CurrentWeapon->StopFire();
	ReloadAnimationInProgress = true;
	CurrentWeapon->Reload();
	PlayAnimMontage(CurrentReloadAnimation);
}
void UBSWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	CurrentWeapon = nullptr;
	for (const auto Weapon : Weapons)
	{
		Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		Weapon->Destroy();
	}
	Weapons.Empty();
	Super::EndPlay(EndPlayReason);
}
