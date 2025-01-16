

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
}

void UBSWeaponComponent::SpawnWeapon()
{
	if(!GetWorld())
	{
		return;
	}
	if(CurrentWeapon = GetWorld()->SpawnActor<ABSBaseWeapon>(WeaponClass))
	{
		if(ACharacter* Character = Cast<ACharacter>(GetOwner()))
		{
			const FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget,false);
			CurrentWeapon->AttachToComponent(Character->GetMesh(),AttachmentRules,WeaponAttachSocket);
			CurrentWeapon->SetOwner(Character);
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
	if(!CurrentWeapon)
	{
		return;
	}
	CurrentWeapon->StopFire();
}
