
#include "Weapon/BSBaseWeapon.h"

#include "BSBaseCharacter.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon, All, All);

ABSBaseWeapon::ABSBaseWeapon()
{
	PrimaryActorTick.bCanEverTick = false;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
	SetRootComponent(MeshComponent);

	CurrentAmmo = DefaultAmmo;
}

void ABSBaseWeapon::StartFire()
{
}

void ABSBaseWeapon::StopFire()
{
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
	DecreaseAmmo();

	if (!HitResult.bBlockingHit)
	{
		DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), TraceEnd, FColor::Red, false, 2.0f);
		return;
	}

	if (AActor* Enemy = Cast<AActor>(HitResult.GetActor()))
	{
		UGameplayStatics::ApplyPointDamage(Enemy, Damage, TraceStart, HitResult, GetPlayerController(), GetOwner(), nullptr);
	}
	DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), HitResult.ImpactPoint, FColor::Red, false, 2.0f);
	DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10, 24, FColor::Red, false, 3.0f);
}
bool ABSBaseWeapon::CanReload()
{
	if(CurrentAmmo.BulletsInClip == DefaultAmmo.BulletsInClip || IsAmmoEmpty())
	{
		return false;
	}
	return true;
}
void ABSBaseWeapon::Reload()
{
	ChangeClip();
}

void ABSBaseWeapon::BeginPlay()
{
	Super::BeginPlay();

	check(MeshComponent);
	checkf(DefaultAmmo.BulletAmount >= 0, TEXT("Bullets count coudn`t be less of zero"));
	checkf(DefaultAmmo.BulletsInClip >= 0, TEXT("Bullets in Clip count coudn`t be less of zero"));
}

APlayerController* ABSBaseWeapon::GetPlayerController() const
{
	if (const ACharacter* Player = Cast<ACharacter>(GetOwner()))
	{
		return Player->GetController<APlayerController>();
	}
	return nullptr;
}

bool ABSBaseWeapon::GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation)
{
	if (const APlayerController* Controller = GetPlayerController())
	{
		Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
		return true;
	}
	return false;
}

FVector ABSBaseWeapon::GetMuzzleWorldLocation() const
{
	return MeshComponent->GetSocketLocation(MuzzleSocketName);
}

bool ABSBaseWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd)
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

	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionParam);
}
void ABSBaseWeapon::DecreaseAmmo()
{
	CurrentAmmo.BulletsInClip--;
	LogAmmo();
	
	if (IsClipEmpty() && CanReload())
	{
		const auto Character = Cast<ACharacter>(GetOwner());
		const auto Mesh = Character->GetMesh();
		OnClipEmptySignature.Broadcast();
	}
}
void ABSBaseWeapon::ChangeClip()
{
	if(!CanReload())
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
void ABSBaseWeapon::LogAmmo()
{
	FString AmmoInfo = "Ammo " + FString::FromInt(CurrentAmmo.BulletsInClip) + " / ";
	AmmoInfo += DefaultAmmo.Infinite ? "Infinite" : FString::FromInt(CurrentAmmo.BulletAmount);
	UE_LOG(LogBaseWeapon, Display, TEXT("%s"), *AmmoInfo);
}
bool ABSBaseWeapon::IsAmmoEmpty() const
{
	return !CurrentAmmo.BulletAmount && IsClipEmpty() && !CurrentAmmo.Infinite;
}
bool ABSBaseWeapon::IsClipEmpty() const
{
	return !CurrentAmmo.BulletsInClip;
}
