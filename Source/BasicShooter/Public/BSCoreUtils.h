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
	
	static FText TextBadResult()
	{
		return UKismetTextLibrary::Conv_StringToText(BadTextResult);
	}
	
	template<typename Structure, typename T>
	static Structure* FindInArrayByProperty(TArray<Structure>& From, const Structure& What, T Structure::* Property)
	{
		return From.FindByPredicate([&](const Structure& Data) {
			return Data.*Property == What.*Property;
		});
	}

	template<typename Structure, typename T>
	static Structure** FindInArrayByClass(TArray<Structure*> From, const T& Value)
	{
		return  From.FindByPredicate([&](const Structure* Data)
					{
						return Data->GetClass() == Value;
					});
	}

	

private:
	inline const static FString BadTextResult = "BadText";
};
