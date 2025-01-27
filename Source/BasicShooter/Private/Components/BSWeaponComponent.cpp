

#include "Components/BSWeaponComponent.h"

#include "GameFramework/Character.h"
#include "Weapon/BSBaseWeapon.h"

UBSWeaponComponent::UBSWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UBSWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	SpawnWeapon();
	EquipWeapon(CurrentWeaponIndex);
}


void UBSWeaponComponent::AttachWeaponToSocket(ABSBaseWeapon* Weapon, USkeletalMeshComponent* SceneComponent, FName SocketName)
{
	const FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	Weapon->AttachToComponent(SceneComponent, AttachmentRules, SocketName);
	
}
void UBSWeaponComponent::EquipWeapon(int32 WeaponIndex)
{
	if(Weapons.IsEmpty())
	{
		return;
	}
	if(const ACharacter* Character = Cast<ACharacter>(GetOwner()))
	{
		if(CurrentWeapon)
		{
			CurrentWeapon->StopFire();
			AttachWeaponToSocket(CurrentWeapon,Character->GetMesh(),WeaponArmorySocket);
		}
		CurrentWeapon = Weapons[WeaponIndex];
		AttachWeaponToSocket(CurrentWeapon,Character->GetMesh(),WeaponAttachSocket);
	}
}
void UBSWeaponComponent::SpawnWeapon()
{
	if(!GetWorld())
	{
		return;
	}
	for(auto WeaponClass : WeaponClasses)
	{
		if(auto Weapon = GetWorld()->SpawnActor<ABSBaseWeapon>(WeaponClass))
		{
			if(ACharacter* Character = Cast<ACharacter>(GetOwner()))
			{

				Weapon->SetOwner(Character);
				Weapons.Add(Weapon);

				AttachWeaponToSocket(Weapon,Character->GetMesh(),WeaponArmorySocket);
			}
		}
	}

}

void UBSWeaponComponent::StartFire()
{
	if(!CurrentWeapon)
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
	CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
	EquipWeapon(CurrentWeaponIndex);
}
void UBSWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	CurrentWeapon = nullptr;
	for(auto Weapon : Weapons)
	{
		Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		Weapon->Destroy();
	}
	Weapons.Empty();
	Super::EndPlay(EndPlayReason);
}
