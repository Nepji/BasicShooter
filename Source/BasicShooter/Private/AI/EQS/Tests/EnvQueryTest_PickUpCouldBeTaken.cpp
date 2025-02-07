// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/EQS/Tests/EnvQueryTest_PickUpCouldBeTaken.h"

#include "EnvironmentQuery/Items/EnvQueryItemType_ActorBase.h"
#include "Pickups/BSBasePickup.h"
UEnvQueryTest_PickUpCouldBeTaken::UEnvQueryTest_PickUpCouldBeTaken(const FObjectInitializer& ObjInit)
	: Super(ObjInit)
{
	Cost = EEnvTestCost::Low;
	ValidItemType = UEnvQueryItemType_ActorBase::StaticClass();
	SetWorkOnFloatValues(false);
}
void UEnvQueryTest_PickUpCouldBeTaken::RunTest(FEnvQueryInstance& QueryInstance) const
{
	const auto DataOwner = QueryInstance.Owner.Get();
	BoolValue.BindData(DataOwner, QueryInstance.QueryID);
	const auto WantsBeTaken = BoolValue.GetValue();
	
	for (FEnvQueryInstance::ItemIterator It(this, QueryInstance); It; ++It)
	{
		const auto ItemActor = GetItemActor(QueryInstance, It.GetIndex());
		const auto PickupActor = Cast<ABSBasePickup>(ItemActor);
		if(!PickupActor)
		{
			continue;
		}
		const auto CouldBeTaken = PickupActor->CouldBeTaken();
		It.SetScore(TestPurpose,FilterType,CouldBeTaken,WantsBeTaken);
	}
}