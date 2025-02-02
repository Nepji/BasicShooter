#pragma once

class BSCoreUtils
{
public:
	template <typename T>
	static T* GetComponent(APawn* Pawn)
	{
		if (!Pawn)
		{
			return nullptr;
		}
		const auto Component = Pawn->GetComponentByClass(T::StaticClass());
		const auto SearchedComponent = Cast<T>(Component);
		return SearchedComponent;
	}
};
