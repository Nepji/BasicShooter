#pragma once

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
};
