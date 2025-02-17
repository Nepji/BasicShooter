
#pragma once

#include "CoreMinimal.h"
#include "Runtime/Core/Public/Containers/Array.h"
#include "EditorUtilityLibrary.generated.h"

UCLASS()
class FAKEUTIL_API UEditorUtilityLibrary
{
	GENERATED_BODY()

public:
	static void	RenameAsset(UObject* Asset, const FString& NewName){};
	static 	TArray<UObject*> GetSelectedAssets() {return TArray<UObject>();};
};