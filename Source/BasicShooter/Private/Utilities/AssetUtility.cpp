// Fill out your copyright notice in the Description page of Project Settings.


#include "Utilities/AssetUtility.h"

#ifdef WITH_EDITOR

#include "EditorUtilityLibrary.h"
#include "Subsystems/EditorAssetSubsystem.h"
#endif

FString UAssetUtility::NewPrefix(UObject *Obj) {
  if (!Obj)
  {
    return UnknownClassPrefix;
  }

  const FString* Prefix = AssetClassToPrefixMap.Find(Obj->GetClass()->GetName());
  return Prefix ? *Prefix : *UnknownClassPrefix;
}


bool UAssetUtility::ExistedPrefix(const FString& OldName) {

  for (auto AssetPrefix : AssetClassToPrefixMap) {
    if (OldName.StartsWith(AssetPrefix.Value))
    {
      return true;
    }
  }
  return false;
}


bool UAssetUtility::ExistedCorrectPrefix(const FString &OldName,
                                          const FString &CorrectPrefix) {

  const FString* Prefix = AssetClassToPrefixMap.Find(OldName.Left(CorrectPrefix.Len()));
  return Prefix && *Prefix == CorrectPrefix;
}


FString UAssetUtility::NewNameWithPrefix(UObject *Obj) {
  if (!Obj) {
    return "";
  }
  const auto ObjName = Obj->GetName();
  const auto CorrectPrefix = NewPrefix(Obj);
  
  if (ExistedPrefix(ObjName)) {
    if (ExistedCorrectPrefix(ObjName, CorrectPrefix)) {
      return ObjName;
    }
    return ChangedPrefix(ObjName, CorrectPrefix);
  }
  return CorrectPrefix + ObjName;
}


FString UAssetUtility::ChangedPrefix(FString Name, const FString& CorrectPrefix)
{
	for (auto AssetPrefix : AssetClassToPrefixMap)
	{
		if (Name.StartsWith(AssetPrefix.Value))
		{
			Name.ReplaceInline(*AssetPrefix.Value, *CorrectPrefix);
			break;
		}
	}
	return Name;
}
void UAssetUtility::RenameAsset(UObject* Asset, const FString& NewName)
{
#ifdef WITH_EDITOR
	UEditorUtilityLibrary::RenameAsset(Asset, NewName);
#endif
}

void UAssetUtility::SetPrefix() {
  TArray<UObject *> AssetsArray = SelectedAssetsArray();

  for (UObject *Asset : AssetsArray) {
    const FString NewName = NewNameWithPrefix(Asset);
  	if(NewName == Asset->GetName())
  	{
  		continue;
  	}
  	RenameAsset(Asset,NewName);
  }
}

TArray<UObject*> UAssetUtility::SelectedAssetsArray()
{
#ifdef WITH_EDITOR
  return UEditorUtilityLibrary::GetSelectedAssets();
#endif
}

void UAssetUtility::RenameAt(const FString From,const FString To) {
  TArray<UObject *> AssetsArray = SelectedAssetsArray();

  for (UObject *Asset : AssetsArray) {
    const FString NewName = Asset->GetName().Replace(*From,*To);
  	RenameAsset(Asset,NewName);
  }
}
