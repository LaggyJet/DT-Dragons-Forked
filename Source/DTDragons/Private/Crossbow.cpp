// Fill out your copyright notice in the Description page of Project Settings.
#include "Crossbow.h"
#include "Arrow.h"
#include "DirectSelector.h"

void UCrossbow::ForePinch(USelector* selector, bool state)
{
	if (state && flag) {
		UVodget::ForePinch(selector, state);
		triggerDelegate.Broadcast(true);
		
		flag = false;

		UArrow* temp = Cast<UArrow>(child);
		TArray<USceneComponent*> toDelete;
		snapJoint->GetChildrenComponents(true, toDelete);
		if (temp) temp->snapper->UnSnap();
		for (int i = 0; i < toDelete.Num(); i++)
		{
			toDelete[i]->DestroyComponent();
		}
		arrowRoot->SetRelativeLocation(FVector::ZeroVector);
	}
}

void UCrossbow::Grip(USelector* selector, bool state)
{
	selector->GrabFocus(state);
	if (state){
		grabbingSelector = selector;
		FTransform selectorLocal = selector->Cursor() * tiltRoot->GetComponentTransform().Inverse();
		initPitchVec = selectorLocal.GetLocation();
		initYawVec = initPitchVec;
		initYawVec.Z = 0;
		initPitchVec.X = 0;


		PrimaryComponentTick.SetTickFunctionEnable(true);
	}
	else {
		grabbingSelector = nullptr;
		PrimaryComponentTick.SetTickFunctionEnable(false);
	}
}

void UCrossbow::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// While grabbing operation is active, calculate the current value of the world cursor in the 
	// crossbows local plane and calculate quaternion that would rotate the initial grabvec into the current.
	// Use this quaternion to spin the dial to follow the grabbing world cursor.
	if(grabbingSelector)
	{
		FVector newSelectorLocal = tiltRoot->GetComponentTransform().InverseTransformPosition(grabbingSelector->Cursor().GetLocation());
		
		FVector turn = newSelectorLocal;
		FVector tilt = newSelectorLocal;
		turn.Z = 0;  tilt.X = 0;

		FQuat turnRot = FQuat::FindBetween(initYawVec, turn);
		FQuat tiltRot = FQuat::FindBetween(initPitchVec, tilt);

		turnRot = turnRoot->GetRelativeTransform().GetRotation() * turnRot;
		tiltRot = tiltRoot->GetRelativeTransform().GetRotation() * tiltRot;

		turnRoot->SetRelativeRotation(turnRot);
		tiltRoot->SetRelativeRotation(tiltRot);
	}
}