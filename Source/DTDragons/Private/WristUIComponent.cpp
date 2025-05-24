// Fill out your copyright notice in the Description page of Project Settings.


#include "WristUIComponent.h"
#include "Components/SkeletalMeshComponent.h"  // Needed for USkeletalMeshComponent
#include "Blueprint/UserWidget.h"             // Needed for UUserWidget

UWristUIComponent::UWristUIComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	SetWidgetSpace(EWidgetSpace::World);
	SetDrawSize(FVector2D(300.0f, 200.0f));
	SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void UWristUIComponent::AttachToHand(USkeletalMeshComponent* HandMesh, FName SocketName)
{
	if (HandMesh)
	{
		AttachToComponent(HandMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, SocketName);
	}
}

void UWristUIComponent::UpdateWristUI(TSubclassOf<UUserWidget> NewWidgetClass)
{
	if (WidgetClass)
	{
		WristUIClass = NewWidgetClass;
		SetWidgetClass(WristUIClass);
	}
}

void UWristUIComponent::BeginPlay()
{
	Super::BeginPlay();

	// Ensure the widget class is set before spawning it
	if (WristUIClass)
	{
		SetWidgetClass(WristUIClass);
	}
}
