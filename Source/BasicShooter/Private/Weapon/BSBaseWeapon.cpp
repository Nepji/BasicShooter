
#include "Weapon/BSBaseWeapon.h"

#include "BSPlayerController.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

ABSBaseWeapon::ABSBaseWeapon()
{
	PrimaryActorTick.bCanEverTick = false;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
	SetRootComponent(MeshComponent);

	WeaponFXComponent = CreateDefaultSubobject<UBSWeaponFXComponent>("WeaponFXComponent");
}

void ABSBaseWeapon::StartFire()
{
	if (IsClipEmpty())
	{
		OnClipEmptySignature.Broadcast();
		return;
	}
	MakeShot();
}

void ABSBaseWeapon::StopFire()
{
}
void ABSBaseWeapon::MakeDamage(const FHitResult& HitResult)
{
	if (const auto DamagedActor = HitResult.GetActor())
	{
		UGameplayStatics::ApplyPointDamage(
			DamagedActor,		   //
			Damage,				   //
			HitResult.ImpactPoint, //
			HitResult,			   //
			GetController(),	   //
			this,				   //
			UDamageType::StaticClass());
	}
}

void ABSBaseWeapon::MakeShot()
{
	if (!GetWorld() || IsAmmoEmpty())
	{
		StopFire();
		return;
	}

	FVector TraceStart, TraceEnd;
	if (!GetTraceData(TraceStart, TraceEnd))
	{
		StopFire();
		return;
	}

	FHitResult HitResult;
	MakeHit(HitResult, TraceStart, TraceEnd);

	FVector TraceFXEnd = TraceEnd;
	if (HitResult.bBlockingHit)
	{
		TraceFXEnd = HitResult.ImpactPoint;
		MakeDamage(HitResult);
		WeaponFXComponent->PlayImpactFX(HitResult);
	}
	DecreaseAmmo();
	SpawnTraceFX(GetMuzzleWorldLocation(), TraceFXEnd);
	UGameplayStatics::SpawnSoundAttached(FireSound, MeshComponent, MuzzleSocketName);
	UGameplayStatics::SpawnSoundAtLocation(GetWorld(), ImpactSound, TraceEnd);
}
bool ABSBaseWeapon::CanReload() const
{
	if (IsAmmoEmpty() || IsClipFull())
	{
		return false;
	}
	return true;
}
void ABSBaseWeapon::Reload()
{
	ChangeClip();
}
FWeaponUIData ABSBaseWeapon::GetUIData() const
{
	return UIData;
}
FAmmoData ABSBaseWeapon::GetDefaultAmmoData() const
{
	return DefaultAmmo;
}
FAmmoData ABSBaseWeapon::GetAmmoData() const
{
	return CurrentAmmo;
}
bool ABSBaseWeapon::TryAddAmmo(int32 AmountOfAmmo)
{
	if (CurrentAmmo.Infinite || IsAmmoFull())
	{
		return false;
	}

	CurrentAmmo.BulletAmount = FMath::Clamp(CurrentAmmo.BulletAmount + AmountOfAmmo, 0, DefaultAmmo.BulletAmount);
	return true;
}

void ABSBaseWeapon::BeginPlay()
{
	Super::BeginPlay();

	check(MeshComponent);
	check(WeaponFXComponent);
	checkf(DefaultAmmo.BulletAmount >= 0, TEXT("Bullets count coudn`t be less of zero"));
	checkf(DefaultAmmo.BulletsInClip >= 0, TEXT("Bullets in Clip count coudn`t be less of zero"));
	CurrentAmmo = DefaultAmmo;
}

AController* ABSBaseWeapon::GetController() const
{
	if (const APawn* Pawn = Cast<APawn>(GetOwner()))
	{
		return Pawn->GetController();
	}
	return nullptr;
}

bool ABSBaseWeapon::GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const
{
	const auto BSCharacter = Cast<ACharacter>(GetOwner());
	if (!BSCharacter)
	{
		return false;
	}
	if (BSCharacter->IsPlayerControlled())
	{
		const auto Controller = Cast<ABSPlayerController>(GetController());
		if (!Controller)
		{
			return false;
		}
		Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
	}
	else
	{
		ViewLocation = GetMuzzleWorldLocation();
		ViewRotation = MeshComponent->GetSocketRotation(MuzzleSocketName);
	}

	return true;
}

FVector ABSBaseWeapon::GetMuzzleWorldLocation() const
{
	return MeshComponent->GetSocketLocation(MuzzleSocketName);
}

bool ABSBaseWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
	FVector ViewLocation;
	FRotator ViewRotation;

	if (!GetPlayerViewPoint(ViewLocation, ViewRotation))
	{
		return false;
	}

	TraceStart = ViewLocation;
	const float HalfRad = FMath::DegreesToRadians(SprayRadius);
	const FVector ShootDirection = FMath::VRandCone(ViewRotation.Vector(), HalfRad);
	TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;

	return true;
}

void ABSBaseWeapon::MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd) const
{
	if (!GetWorld())
	{
		return;
	}
	FCollisionQueryParams CollisionParam;
	CollisionParam.AddIgnoredActor(GetOwner());
	CollisionParam.bReturnPhysicalMaterial = true;

	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionParam);
}
void ABSBaseWeapon::DecreaseAmmo()
{
	CurrentAmmo.BulletsInClip--;
}
void ABSBaseWeapon::ChangeClip()
{
	if (!CanReload())
	{
		return;
	}
	if (!DefaultAmmo.IgnoreRemainingBullets)
	{
		CurrentAmmo.BulletAmount += CurrentAmmo.BulletsInClip;
	}

	const int32 BulletsToReload = FMath::Min(CurrentAmmo.BulletAmount, DefaultAmmo.BulletsInClip);
	CurrentAmmo.BulletsInClip = BulletsToReload;

	if (!DefaultAmmo.Infinite)
	{
		CurrentAmmo.BulletAmount -= BulletsToReload;
	}
}

bool ABSBaseWeapon::IsAmmoEmpty() const
{
	return !CurrentAmmo.BulletAmount && IsClipEmpty() && !CurrentAmmo.Infinite;
}
bool ABSBaseWeapon::IsClipEmpty() const
{
	return CurrentAmmo.BulletsInClip <= 0;
}
bool ABSBaseWeapon::IsAmmoFull() const
{
	return CurrentAmmo.BulletAmount == DefaultAmmo.BulletAmount;
}
bool ABSBaseWeapon::IsClipFull() const
{
	return CurrentAmmo.BulletsInClip == DefaultAmmo.BulletsInClip;
}
UNiagaraComponent* ABSBaseWeapon::SpawnMuzzleFX() const
{
	return UNiagaraFunctionLibrary::SpawnSystemAttached(
		MuzzleFX,
		MeshComponent,
		MuzzleSocketName,
		FVector::ZeroVector,
		FRotator::ZeroRotator,
		EAttachLocation::SnapToTarget,
		true);
}
void ABSBaseWeapon::SpawnTraceFX(const FVector& TraceStart, const FVector& TraceEnd) const
{
	if (const auto TraceFXComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), TraceFX, TraceStart))
	{
		TraceFXComponent->SetNiagaraVariableVec3(TraceTargetName, TraceEnd);
	}
}
