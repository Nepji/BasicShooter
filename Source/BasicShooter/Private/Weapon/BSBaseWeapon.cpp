
#include "Weapon/BSBaseWeapon.h"


ABSBaseWeapon::ABSBaseWeapon()
{
	PrimaryActorTick.bCanEverTick = false;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
	SetRootComponent(MeshComponent);
}

void ABSBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABSBaseWeapon::Fire()
{
	
}


