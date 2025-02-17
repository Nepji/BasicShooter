// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/BSBaseWidget.h"

#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
void UBSBaseWidget::Show()
{
	PlayAnimation(ShowAnimation);
	UGameplayStatics::PlaySound2D(GetWorld(), OpenSound);
}