

#include "Components/BSWeaponComponent.h"

#include "BSBaseCharacter.h"
#include "BSCoreUtils.h"
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

	checkf(WeaponsData.Num() <= WeaponMaxNum && WeaponsData.Num(), TEXT("Those character can hold up to &i weapon items"),WeaponMaxNum);
	SpawnWeapon();
	EquipWeapon(CurrentWeaponIndex);
	InitAnimations();
}


void UBSWeaponComponent::AttachWeaponToSocket(ABSBaseWeapon* Weapon, USkeletalMeshComponent* SceneComponent, FName SocketName)
{
	const FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	Weapon->AttachToComponent(SceneComponent, AttachmentRules, SocketName);
}
bool UBSWeaponComponent::SpawnOneWeapon(const FWeaponData& OneWeaponData)
{
	const auto Weapon = GetWorld()->SpawnActor<ABSBaseWeapon>(OneWeaponData.WeaponClass);
	if (!Weapon)
	{
		return false;
	}
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character)
	{
		return false;
	}
	Weapon->OnClipEmptySignature.AddUObject(this, &UBSWeaponComponent::OnEmptyClip);
	Weapon->SetOwner(Character);
	Weapons.Add(Weapon);

	AttachWeaponToSocket(Weapon, Character->GetMesh(), CurrentWeaponSocket(GetClass()));
	return true;
}
void UBSWeaponComponent::EquipWeapon(int32 WeaponIndex)
{
	if (Weapons.IsEmpty() || !FMath::IsWithinInclusive(WeaponIndex, 0, Weapons.Num()))
	{
		return;
	}
	
	ReloadAnimationInProgress = false;
	if (const ACharacter* Character = Cast<ACharacter>(GetOwner()))
	{
		if (CurrentWeapon)
		{
			CurrentWeapon->StopFire();
			AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), CurrentWeaponSocket(CurrentWeapon->GetClass()));
		}
		CurrentWeapon = Weapons[WeaponIndex];
		CurrentReloadAnimation = WeaponsData.FindByPredicate(
											   [&](const FWeaponData& Data) {
												   return Data.WeaponClass == CurrentWeapon->GetClass();
											   })
									 ->ReloadAnimation;
		if(!CurrentReloadAnimation)
		{
			return;
		}
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
	for (auto OneWeaponData : WeaponsData)
	{
		SpawnOneWeapon(OneWeaponData);
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
void UBSWeaponComponent::InitOneAnimation(const FWeaponData& WeaponData)
{
	if (const auto ReloadAnimationFinished = AnimUtils::FindNotifyByClass<UBSReloadFinishedAnimNotify>(WeaponData.ReloadAnimation))
	{
		ReloadAnimationFinished->OnNotifiedSignature.AddUObject(this, &UBSWeaponComponent::OnReloadFinished);
	}
	else
	{
		if(WeaponData.ReloadAnimation != nullptr)
		{
			UE_LOG(LogWeaponComponent,Error,TEXT("AnimNotify \"%s\" for weapon %s not found"),*WeaponData.ReloadAnimation->GetName(),*WeaponData.WeaponClass->GetName());
		}
		else
		{
			UE_LOG(LogWeaponComponent,Error,TEXT("Reload Animation for weapon %s not found"),*WeaponData.WeaponClass->GetName());
		}
		checkNoEntry();
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
	for (const auto OneWeaponData : WeaponsData)
	{
		InitOneAnimation(OneWeaponData);
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
			CurrentWeapon->Reload();
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
	if(!MovementComponent)
	{
		return false;
	}
	return !EquipAnimationInProgress && CurrentWeapon && !Character->IsRunning() && !MovementComponent->IsFalling() && !ReloadAnimationInProgress;
}
bool UBSWeaponComponent::CanReload() const
{
	return !ReloadAnimationInProgress && CurrentWeapon->CanReload();
}
bool UBSWeaponComponent::IsWeaponsNeedToReload() const
{
	for (const auto Weapon : Weapons)
	{
		if(IsCurrentWeaponEmpty(Weapon))
		{
			return true;
		}
	}
	return false;
}
bool UBSWeaponComponent::IsCurrentWeaponEmpty(const ABSBaseWeapon* Weapon) const
{
	if (!Weapon)
	{
		return false;
	}
	return Weapon->IsClipEmpty() && Weapon->CanReload();
}
float UBSWeaponComponent::GetCurrentAmmoLoadPercent() const
{
	if(!CurrentWeapon)
	{
		return 0.0f;
	}
	const auto CurrentAmmo = CurrentWeapon->GetAmmoData().BulletAmount;
	const auto DefaultAmmo = CurrentWeapon->GetDefaultAmmoData().BulletAmount;
	return CurrentAmmo/DefaultAmmo;
	
}

void UBSWeaponComponent::OnEmptyClip()
{
	ChangeClip();
}
bool UBSWeaponComponent::ReplaceableWeapon(FWeaponData& ReplaceableWeaponData)
{
	if(WeaponsData.IsEmpty())
	{
		return false;
	}
	const auto WeaponDataStruct = WeaponsData.FindByPredicate([&](const FWeaponData& Data) {
												return Data.Replaceable;
											});
	if (!WeaponDataStruct)
	{
		return false;
	}
	ReplaceableWeaponData = *WeaponDataStruct;
	return true;
}

void UBSWeaponComponent::Reload()
{
	ChangeClip();
}
bool UBSWeaponComponent::GetWeaponUIData(FWeaponUIData& UIData) const
{
	if (CurrentWeapon)
	{
		UIData = CurrentWeapon->GetUIData();
		return true;
	}
	return false;
}
bool UBSWeaponComponent::GetWeaponAmmoData(FAmmoData& AmmoData) const
{
	if (CurrentWeapon)
	{
		AmmoData = CurrentWeapon->GetAmmoData();
		return true;
	}
	return false;
}
void UBSWeaponComponent::ChangeClip()
{
	if (!CanReload())
	{
		return;
	}
	CurrentWeapon->StopFire();
	ReloadAnimationInProgress = true;
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
bool UBSWeaponComponent::TryToAddAmmo(int32 AmountOfAmmo, TSubclassOf<ABSBaseWeapon> WeaponType)
{
	bool bSuccess = false;
	for (const auto Weapon : Weapons)
	{
		if (!Weapon)
		{
			continue;
		}
		if (!WeaponType || Weapon->IsA(WeaponType))
		{
			if (Weapon->TryAddAmmo(AmountOfAmmo))
			{
				bSuccess = true;
			}
		}
	}
	return bSuccess;
}

bool UBSWeaponComponent::TryToRemoveWeapon(FWeaponData& WeaponData)
{
	if (!CurrentWeapon)
	{
		return false;
	}

	if (CurrentWeapon->GetClass() == WeaponData.WeaponClass)
	{
		NextWeapon();
	}
	const auto WeaponPtr = BSCoreUtils::FindInArrayByClass<ABSBaseWeapon>(Weapons, WeaponData.WeaponClass);
	if (!WeaponPtr)
	{
		return false;
	}
	Weapons.Remove(*WeaponPtr);
	
	return true;
}
bool UBSWeaponComponent::TryPickupWeapon(const FWeaponData& WeaponData)
{
	if (Weapons.ContainsByPredicate([&](const ABSBaseWeapon* Weapon) {
										return Weapon && Weapon->GetClass() == WeaponData.WeaponClass;
								}))
	{
		return false;
	}
	if(Weapons.Num() >= MaxEquipWeapons)
	{
		FWeaponData ReplaceableWeaponData;
		if(!ReplaceableWeapon(ReplaceableWeaponData))
		{
			return false;
		}
		WeaponsData.Remove(WeaponData);
		if(!TryToRemoveWeapon(ReplaceableWeaponData))
		{
			return false;
		}
	}
	const auto WeaponDataUnit = BSCoreUtils::FindInArrayByProperty<FWeaponData>(WeaponsData,WeaponData,&FWeaponData::WeaponClass);

	if(!WeaponDataUnit)
	{
		WeaponsData.Add(WeaponData);
		InitOneAnimation(WeaponData);
	}
	SpawnOneWeapon(WeaponData);

	return false;
}
