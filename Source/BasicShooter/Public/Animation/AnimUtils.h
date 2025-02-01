#pragma once

class AnimUtils
{
public:
	template <typename T>
	static T* FindNotifyByClass(UAnimSequenceBase* Animation)
	{
		if (!Animation)
		{
			return nullptr;
		}
		const auto NotifyEvents = Animation->Notifies;
		for (auto NotifyEvent : NotifyEvents)
		{
			auto FinishedNotify = Cast<T>(NotifyEvent.Notify);
			if (FinishedNotify)
			{
				return FinishedNotify;
			}
		}
		return nullptr;
	}
};
