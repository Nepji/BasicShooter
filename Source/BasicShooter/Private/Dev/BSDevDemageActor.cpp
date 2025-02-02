


#include "Dev/BSDevDemageActor.h"

#include "Kismet/GameplayStatics.h"

ABSDevDamegeActor::ABSDevDamegeActor()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);

}

void ABSDevDamegeActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABSDevDamegeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DrawDebugSphere(GetWorld(),GetActorLocation(),Radius,24,SphereColor);

	UGameplayStatics::ApplyRadialDamage(GetWorld(),(Heal?-FMath::Abs(Damage):Damage), GetActorLocation(),Radius,nullptr,{},this,nullptr, CentreFullDamage);
}

