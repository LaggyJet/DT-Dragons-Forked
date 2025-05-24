// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"



void UGun::BeginPlay()
{
	Super::BeginPlay();
	clientComponent = GetAttachmentRoot();
	snapper->Init(clientComponent, snapJoint, this, false);
}

void UGun::ForePinch(USelector* cursor, bool state)
{
// fire bullet

	if (state) {
		UVodget::ForePinch(cursor, state);
		triggerDelegate.Broadcast(true);
	}

}

void UGun::Grip(USelector* cursor, bool state)
{
	//Super::Grip(cursor, state);
	if (grabbingSelector && grabbingSelector != cursor) {
		return;
	}

	if(snapper && snapper->isSnapped) PrimaryComponentTick.SetTickFunctionEnable(true);
	else PrimaryComponentTick.SetTickFunctionEnable(state);

	cursor->GrabFocus(state);
	grabbingSelector = state ? cursor : nullptr;

	//if (state) {
	//	childsrt = clientComponent->GetComponentTransform() * cursor->Cursor().Inverse();
	//}
}

void UGun::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	//FTransform trans = childsrt * grabbingSelector->Cursor();

	//// offset is configured to be the HandleDock static mesh
	//trans.SetLocation(trans.GetLocation() + offset->GetRelativeLocation() );
	//clientComponent->SetWorldTransform(trans);

	if (snapper && snapper->isSnapped)
	{
		clientComponent->SetWorldLocationAndRotation(snapper->snappedTo->GetComponentLocation(), snapper->snappedTo->GetComponentRotation());
		snapper->canSnap = false;
		if(grabbingSelector)
		{
			FVector loc = grabbingSelector->Cursor().GetLocation();
			FVector gunLoc = clientComponent->GetComponentLocation();
			if (FVector::Distance(loc, gunLoc) > disconnectDist) snapper->UnSnap();
		}
	}
	else if (grabbingSelector)
	{
		FTransform loc = offset->GetRelativeTransform() * grabbingSelector->Cursor();
		clientComponent->SetWorldTransform(loc);
		if(snapper) snapper->canSnap = true;
	}
}


