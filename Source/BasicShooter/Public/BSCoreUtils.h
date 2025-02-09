#pragma once
#include "BSPlayerState.h"
#include "Kismet/KismetTextLibrary.h"

class UKismetTextLibrary;
class BSCoreUtils
{
public:
	template <typename T>
	static T* GetActorComponent(AActor* Actor)
	{
		if (!Actor)
		{
			return nullptr;
		}
		const auto Component = Actor->GetComponentByClass(T::StaticClass());
		const auto SearchedComponent = Cast<T>(Component);
		return SearchedComponent;
	}

	static bool AreEnemies(AController* Controller1, AController* Controller2)
	{
		if(!Controller1 || !Controller2 || Controller1 == Controller2)
		{
			return false;
		}
		const auto PlayerState1 = Cast<ABSPlayerState>(Controller1->PlayerState);
		const auto PlayerState2 = Cast<ABSPlayerState>(Controller2->PlayerState);
		return PlayerState1 && PlayerState2 && PlayerState1->GetTeamID() != PlayerState2->GetTeamID();
	}

	static FString StringBadResult()
	{
		return BadTextResult;
	}
	static FText TextBadResult()
	{
		return UKismetTextLibrary::Conv_StringToText(BadTextResult);
	}

private:
	inline const static FString BadTextResult = "BadText";
};
