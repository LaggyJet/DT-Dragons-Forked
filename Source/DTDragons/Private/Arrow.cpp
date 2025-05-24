// Fill out your copyright notice in the Description page of Project Settings.


#include "Arrow.h"
#include "Crossbow.h"

void UArrow::BeginPlay()
{
	Super::BeginPlay();

	clientComponent = GetAttachmentRoot();
	snapper->Init(clientComponent, snapJoint, this, false);
}

void UArrow::Grip(USelector* selector, bool state)
{
	Super::Grip(selector, state);
	if (grabbingSelector && grabbingSelector != selector)
	{
		if (state)
		{
			grabbingSelector->GrabFocus(false);
		}
		else
		{
			grabbingSelector->GrabFocus(state);
			return;
		}
	}
	selector->GrabFocus(state);
	stabber->canStab = state;
	if (state) {
		grabbingSelector = selector;
		childsrt = clientComponent->GetComponentTransform() * selector->Cursor().Inverse();
		initPos = std::numeric_limits<float>::max();
		PrimaryComponentTick.SetTickFunctionEnable(true);
	}
	else {
		initPos = std::numeric_limits<float>::max();
		grabbingSelector = nullptr;
		PrimaryComponentTick.SetTickFunctionEnable(false);
	}
}

void UArrow::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	//if snapped run arrow code
	if (snapper->isSnapped)
	{
		if(!snapper->isOriented) 
		{
			parent->canSnapTo = false;
			snapper->Orient();
		}
		if(initPos == std::numeric_limits<float>::max()) initPos = clientComponent->GetComponentTransform().InverseTransformPosition(grabbingSelector->Cursor().GetLocation()).Z;
		if (!parentClient) parentClient = Cast<UCrossbow>(parent)->arrowRoot;
		if (drawn && !flag)
		{
			parentClient->SetRelativeLocation(FVector::Zero());
			drawn = false;
			flag = false;
			parent->canSnapTo = true;
			TArray<USceneComponent*> children;
			snapJoint->GetChildrenComponents(true, children);
			for (int i = 0; i < children.Num(); i++)
			{
				children[i]->DestroyComponent();
			}
		}
		if (!drawn && grabbingSelector)
		{
			FVector newPos = parentClient->GetComponentTransform().InverseTransformPosition(grabbingSelector->Cursor().GetLocation());
			float deltaZ = newPos.Z - initPos;
			FVector sliderPos = parentClient->GetRelativeLocation();
			sliderPos.Z += deltaZ;
			if (sliderPos.Z <= minval)
			{
				drawn = true;
				parent->flag = true;
			}
			sliderPos.Z = FMath::Clamp(sliderPos.Z, minval, maxval);
			parentClient->SetRelativeLocation(sliderPos);
		}
	}
	//else run grabber code
	else
	{
		if (grabbingSelector)
		{
			FTransform newT = (childsrt * grabbingSelector->Cursor());
			clientComponent->SetWorldTransform(newT);
			clientComponent->SetWorldRotation(newT.GetRotation());
		}
	}
}