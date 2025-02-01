// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Notify/BSAnimNotify.h"

void UBSAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	OnNotifiedSignature.Broadcast(MeshComp);
	Super ::Notify(MeshComp, Animation);
}
