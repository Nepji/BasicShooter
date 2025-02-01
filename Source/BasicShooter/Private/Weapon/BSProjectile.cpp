


#include "Weapon/BSProjectile.h"
#include "Kismet/GameplayStatics.h"

ABSProjectile::ABSProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
	CollisionComponent = CreateDefaultSubobject<USphereComponent>("CollisionComponent");
	CollisionComponent->IgnoreActorWhenMoving(GetOwner(),true);
	CollisionComponent->InitSphereRadius(15.0f);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndProbe);
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);

	SetRootComponent(CollisionComponent);

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
	MeshComponent->SetupAttachment(GetRootComponent());

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComponent");
	MovementComponent->InitialSpeed = 20.0f;
}

void ABSProjectile::OnProjectileHit(
	UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if(!GetWorld())
	{
		return;
	}
	MovementComponent->StopMovementImmediately();
	UGameplayStatics::ApplyRadialDamage(
		GetWorld(),					//
		DamageAmount,				//
		GetActorLocation(),			//
		DamageRadius,				//
		UDamageType::StaticClass(), //
		{ GetOwner() },			    //
		this,						//
		GetController(),			//
		CentreFullDamage);			//
	DrawDebugSphere(GetWorld(),GetActorLocation(),DamageRadius,24,FColor::Red,false, 5.0f);
	Destroy();
}
void ABSProjectile::BeginPlay()
{
	Super::BeginPlay();

	check(MovementComponent);
	CollisionComponent->OnComponentHit.AddDynamic(this, &ABSProjectile::OnProjectileHit);
	MovementComponent->Velocity = ShotDirection * MovementComponent->InitialSpeed;
	GetWorldTimerManager().SetTimer(ProjectileLifeSpanHandle,this,&ABSProjectile::LifeSpanOver,ProjectileLifeSpan,false);
}

AController* ABSProjectile::GetController() const
{
	const auto Pawn = Cast<APawn>(GetOwner());
	return Pawn ? Pawn->GetController() : nullptr;
}
void ABSProjectile::LifeSpanOver()
{
	MovementComponent->StopMovementImmediately();
	Destroy();
}

void ABSProjectile::SetShotDirection(const FVector& Direction)
{
	ShotDirection = Direction;
}

