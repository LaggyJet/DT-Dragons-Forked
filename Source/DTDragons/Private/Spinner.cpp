// Fill out your copyright notice in the Description page of Project Settings.


#include "Spinner.h"

// Sets default values for this component's properties
USpinner::USpinner()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void USpinner::BeginPlay()
{
	Super::BeginPlay();

	PrimaryComponentTick.bCanEverTick = true;
}


// Called every frame
void USpinner::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (glow && glowLight) glowLight->SetVisibility(spin);
	if (spin)
	{
		if(root) 
		{
			/*FVector worldVec = root->GetComponentLocation();
			worldVec.Z = verticalOffset;
			root->SetWorldLocation(worldVec);*/
			FRotator newRotation = FRotator(0, 1, 0);
			root->AddWorldRotation(newRotation);
		}
	}
}

