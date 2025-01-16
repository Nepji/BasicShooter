
#include "Weapon/BSBaseWeapon.h"

#include "BSBaseCharacter.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

ABSBaseWeapon::ABSBaseWeapon()
{
	PrimaryActorTick.bCanEverTick = false;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
	SetRootComponent(MeshComponent);
}
void ABSBaseWeapon::StartFire()
{
}
void ABSBaseWeapon::StopFire()
{
}
void ABSBaseWeapon::MakeShot()
{
}

void ABSBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
}

APlayerController* ABSBaseWeapon::GetPlayerController() const 
{
	if(const ACharacter* Player = Cast<ACharacter>(GetOwner()))
	{
		return Player->GetController<APlayerController>();
	}
	return nullptr;
}

bool ABSBaseWeapon::GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation)
{
	if(const APlayerController* Controller = GetPlayerController())
	{
		Controller->GetPlayerViewPoint(ViewLocation,ViewRotation);
		return true;
	}
	return false;
}

FVector ABSBaseWeapon::GetMuzzleWorldLocation() const
{
	return  MeshComponent->GetSocketLocation(MuzzleSocketName);
}

bool ABSBaseWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd)
{
	FVector ViewLocation;
	FRotator ViewRotation;
	
	if(!GetPlayerViewPoint(ViewLocation,ViewRotation))
	{
		return false;
	}
	
	TraceStart = ViewLocation;
	const float HalfRad =	FMath::DegreesToRadians(SprayRadius);
	const FVector ShootDirection =  FMath::VRandCone(ViewRotation.Vector(),HalfRad);
	TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
	
	return true;
}

void ABSBaseWeapon::MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd) const
{
	if(!GetWorld())
	{
		return; 
	}
	FCollisionQueryParams CollisionParam;
	CollisionParam.AddIgnoredActor(GetOwner());

	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart,TraceEnd,ECollisionChannel::ECC_Visibility, CollisionParam);
}
