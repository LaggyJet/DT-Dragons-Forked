// Fill out your copyright notice in the Description page of Project Settings.


#include "Snapper.h"
#include "DirectSelector.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMeshSocket.h"

void USnapper::Init(USceneComponent* ownerArg, USphereComponent* snapColliderArg, UTacVodget* parentVodgetArg, bool selfDestructArg)
{
	owner = ownerArg;
	snapCollider = snapColliderArg;
	parentVodget = parentVodgetArg;
	if (snapCollider)
	{
		snapCollider->SetGenerateOverlapEvents(true);
		snapCollider->OnComponentBeginOverlap.AddDynamic(this, &USnapper::OnOverlapBegin);
	}
}



void USnapper::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (canSnap) Snap(OtherComp);
}

void USnapper::Snap(UPrimitiveComponent* OtherComp)
{
	if (isSnapped) return;
	TArray<USceneComponent*> check;
	OtherComp->GetChildrenComponents(false, check);
	if (check.Num() > 0) return;
	

	TArray<UTacVodget*> foundVodgets;


	TArray<USceneComponent*> Children;
	OtherComp->GetAttachmentRoot()->GetChildrenComponents(true, Children);

	for (int i = 0; i < Children.Num(); i++)
	{
		UTacVodget* foundVodget = Cast<UTacVodget>(Children[i]);
		if (foundVodget)
			foundVodgets.Add(foundVodget);
	}

	if (foundVodgets.IsEmpty())
	{
		FString snapJoint = snapCollider->GetName();
		FString foundCollider = OtherComp->GetName();

		if(!foundCollider.StartsWith(snapJoint))
			return;

		owner->AttachToComponent(OtherComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		snappedTo = Cast<USphereComponent>(OtherComp);
		isSnapped = true;
		owner->SetComponentTickEnabled(true);
		FString temp;
		snappedTo->GetName(temp);
		resetName = new FString(temp);
		occupyName = new FString(temp.Reverse());
		snappedTo->Rename(**occupyName);
	}


	for (int i = 0; i < foundVodgets.Num(); i++)
	{
		FString ownerName = parentVodget->GetName();
		FString foundName = foundVodgets[i]->GetName();
		UE_LOG(LogTemp, Display, TEXT("Owner Name : %s"), *FString(ownerName));
		UE_LOG(LogTemp, Display, TEXT("Found Name : %s"), *FString(foundName));

		FString snapJoint = snapCollider->GetName();
		FString foundSnapJoint = "";
		if (foundVodgets[i]->snapJoint)
			foundSnapJoint = foundVodgets[i]->snapJoint->GetName();

		if (ownerName.Equals(foundName) || !snapJoint.Equals(foundSnapJoint))
			continue;

		if (foundVodgets[i]->canSnapTo)
		{
			parentVodget->SetParent(foundVodgets[i]);
			foundVodgets[i]->SetChild(parentVodget);
			snappedTo = Cast<USphereComponent>(foundVodgets[i]->snapJoint);
			owner->AttachToComponent(snappedTo, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
			isSnapped = true;
			FString temp;
			snappedTo->GetName(temp);
			resetName = new FString(temp);
			occupyName = new FString(temp.Reverse());
			snappedTo->Rename(**occupyName);
		}
	}
}

void USnapper::UnSnap()
{
	if (parentVodget && parentVodget->GetParent())
	{
		parentVodget->GetParent()->SetChild(nullptr);
		parentVodget->SetParent(nullptr);
	}
	owner->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	isSnapped = false;
	snappedTo->Rename(**resetName);
	delete resetName;
	resetName = nullptr;
	delete occupyName;
	occupyName = nullptr;
}

void USnapper::Orient()
{
	if (isSnapped) 
	{
		if (!isOriented)
		{
			owner->SetRelativeTransform(FTransform::Identity);
			owner->SetWorldScale3D(FVector::One());
			if (destructChildren)
			{
				for (int i = 0; i < destroyOnSnap.Num(); i++)
				{
					destroyOnSnap[i]->DestroyComponent();
				}
			}
			if (selfDestruct) DestroyComponent();
			isOriented = true;
		}
	}
}
