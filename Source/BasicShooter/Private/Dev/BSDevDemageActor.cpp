


#include "Dev/BSDevDemageActor.h"

#include "Kismet/GameplayStatics.h"

ABSDevDemageActor::ABSDevDemageActor()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneConponent");
	SetRootComponent(SceneComponent);

}

void ABSDevDemageActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABSDevDemageActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DrawDebugSphere(GetWorld(),GetActorLocation(),Radius,24,SphereColor);

	UGameplayStatics::ApplyRadialDamage(GetWorld(),(Heal?-FMath::Abs(Damage):Damage), GetActorLocation(),Radius,nullptr,{},this,nullptr, CentreFullDamage);
}

