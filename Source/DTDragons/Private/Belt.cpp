// Fill out your copyright notice in the Description page of Project Settings.


#include "Belt.h"

// Sets default values for this component's properties
UBelt::UBelt()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBelt::BeginPlay()
{
	Super::BeginPlay();

	
	beltRoot = GetAttachParent();
}


// Called every frame
void UBelt::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!camera) return;

	beltLoc = camera->GetComponentLocation();
	beltRot = camera->GetComponentRotation().Quaternion();

	beltOffset = FVector::Zero();
	beltOffset.Z = heightOffset;
	beltOffset.X = forwardOffset;

	beltRot.X = 0;
	beltRot.Y = 0;
	beltRot.Normalize();

	beltOffset = beltRot.RotateVector(FVector(forwardOffset, 0, heightOffset));

	beltRoot->SetWorldLocation(beltLoc + beltOffset);
	beltRoot->SetWorldRotation(beltRot);
}
