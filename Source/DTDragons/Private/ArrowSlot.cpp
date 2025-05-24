// Fill out your copyright notice in the Description page of Project Settings.


#include "ArrowSlot.h"

void UArrowSlot::Grip(USelector* cursor, bool state)
{
	if (flag)
	{
		PrimaryComponentTick.SetTickFunctionEnable(true);
		cursor->GrabFocus(state);
		if (state) {
			// Save the grabbing selector.
			grabbingSelector = cursor;
			initPos = clientComponent->GetComponentTransform().InverseTransformPosition(grabbingSelector->Cursor().GetLocation()).Z;
			
		}
		else {
			// Clear the grabbing selector.
			grabbingSelector = nullptr;
		}
	}
}

void UArrowSlot::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	if (drawn && !flag)
	{
		clientComponent->SetRelativeLocation(FVector::Zero());
		drawn = false;
		flag = false;
		TArray<USceneComponent*> children;
		connectJoint->GetChildrenComponents(true, children);
		for (int i = 0; i < children.Num(); i++)
		{
			children[i]->DestroyComponent();
		}
	}
	if(!drawn && grabbingSelector)
	{
		FVector newPos = clientComponent->GetComponentTransform().InverseTransformPosition(grabbingSelector->Cursor().GetLocation());
		float deltaZ = newPos.Z - initPos;

		FVector sliderPos = clientComponent->GetRelativeLocation();
		sliderPos.Z += deltaZ;

		if (sliderPos.Z <= minval)
		{
			drawn = true;
			owner->flag = true;
		}

		sliderPos.Z = FMath::Clamp(sliderPos.Z, minval, maxval);
		
		clientComponent->SetRelativeLocation(sliderPos);
	}
}
