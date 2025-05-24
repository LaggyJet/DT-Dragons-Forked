#ifdef DEBUG

#include "DirectSelector.h"
#include "Vodget.h"

void UDirectSelector::BeginPlay() {
    Super::BeginPlay();
    if (marker) {
		if (UStaticMeshComponent* SphereMeshComponent = Cast<UStaticMeshComponent>(marker)) {
			SphereMeshComponent->SetGenerateOverlapEvents(true);
			SphereMeshComponent->OnComponentBeginOverlap.AddDynamic(this, &UDirectSelector::OnOverlapBegin);
			SphereMeshComponent->OnComponentEndOverlap.AddDynamic(this, &UDirectSelector::OnOverlapEnd);
		}
    }
}

void UDirectSelector::ReplaceFocusVodget(UVodget* vodget)
{
	focusVodget = vodget;
}

void UDirectSelector::SetCursor() { if (marker) cursor = marker->GetComponentTransform(); }

void UDirectSelector::GrabFocus(bool val) {
	Super::GrabFocus(val);

	if (focusVodget && focusWillBeLostOnRelease)
		focusVodget->Focus(this, val);
}

void UDirectSelector::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	TArray<USceneComponent*> children;
	OtherComp->GetChildrenComponents(false, children);
	for (int i = 0; i < children.Num(); i++) {
		UVodget* valid = Cast<UVodget>(children[i]);
		if (valid && !focusVodget)
			focusVodget = valid;
		else if (valid && valid == focusVodget)
			focusWillBeLostOnRelease = false;
	}
}

void UDirectSelector::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {	
	UVodget* valid = Cast<UVodget>(OverlappedComponent);
	if (focusVodget && !focus_grabbed) {
		focusVodget->Focus(this, false);
		focusVodget = nullptr;
	}
	else if (valid && valid == focusVodget)
		focusWillBeLostOnRelease = true;
}

#endif // DEBUG

// Fill out your copyright notice in the Description page of Project Settings.


#include "DirectSelector.h"
#include "Vodget.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"

// Sets default values for this component's properties
UDirectSelector::UDirectSelector()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UDirectSelector::BeginPlay()
{
	Super::BeginPlay();

	// ToDo: In the DirectPawn blueprint, add sphere components to the left and right hands
	// and configure the sphere collision physics to send overlap events.

	// Next, in this method, cast the hands SceneComponent to UStaticMeshComponent and
	// add overlap begin and end callbacks to the child mesh.
	// Hint: An alternative method might be to set the mesh as a property and configure in the pawn.

	UStaticMeshComponent* mesh = Cast<UStaticMeshComponent>(marker);
	if (mesh != nullptr)
	{
		mesh->OnComponentBeginOverlap.AddDynamic(this, &UDirectSelector::OnOverlapBegin);       // set up a notification for when this component overlaps something
		mesh->OnComponentEndOverlap.AddDynamic(this, &UDirectSelector::OnOverlapEnd);       // set up a notification for when this component overlaps something
	}
}

void UDirectSelector::SetCursor()
{
	// Set the cursor FTransform to the world location of the hand.
	cursor = marker->GetComponentTransform();
	cursor.SetScale3D(FVector::One());
}

void UDirectSelector::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Search for Vodget components even when focus is grabbed.
	// When focus is grabbed it is possible to exit our current focusVodget. If this occurs 
	// we keep track of the exit to allow focus to be lost when focus grab is released.

	//UVodget* hitVodget = nullptr;
	//for (int i = 0; i < OtherComp->GetNumChildrenComponents(); i++) {
	//	hitVodget = Cast<UVodget>(OtherComp->GetChildComponent(i));
	//	if (hitVodget != nullptr)
	//		break;
	//}

	//UVodget* hitVodget = OtherActor->GetComponentByClass<UVodget>();
	UVodget* hitVodget = nullptr;
	for (int i = 0; i < OtherComp->GetNumChildrenComponents(); i++) {
		hitVodget = Cast<UVodget>(OtherComp->GetChildComponent(i));
		if (hitVodget != nullptr)
		{
			if (focus_grabbed)
			{
				// Re-entered grabbed vodget
				if (hitVodget == focusVodget) {
					focusWillBeLostOnRelease = false;
					//UE_LOG(LogTemp, Warning, TEXT("Reentered when grabbed:%s"), *FString(focusVodget->GetOwner()->GetActorLabel()));
				}
			}
			else if (hitVodget != focusVodget)
			{
				// Let the previous focusVodgetCurr know that it has lost focus here.
				if (focusVodget != nullptr) {
					focusVodget->Focus(this, false);
					//UE_LOG(LogTemp, Warning, TEXT("Focus FALSE:%s"), *FString(focusVodget->GetOwner()->GetActorLabel()));
				}

				focusVodget = hitVodget;

				// Let the focusVodgetCurr know that it now has selector focus here.
				focusVodget->Focus(this, true);
				focusWillBeLostOnRelease = false;
				//UE_LOG(LogTemp, Warning, TEXT("Focus TRUE:%s"), *FString(focusVodget->GetOwner()->GetActorLabel()));
			}
			return;
		}
	}

	//UE_LOG(LogTemp, Warning, TEXT("OverlappedComp:%s"), *FString( OverlappedComp->GetName() ));
	//UE_LOG(LogTemp, Warning, TEXT("OthComp:%s"), *FString(OtherComp->GetName()));

}

void UDirectSelector::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// Release focusVodget when focus is not grabbed.
	// When focus is grabbed it is possible to re-enter our current focusVodget. If this occurs 
	// we keep track of the re-entry to prevent focus from being lost when focus grab is released.

	//UVodget* hitVodget = OtherActor->GetComponentByClass<UVodget>();
	UVodget* hitVodget = nullptr;
	for (int i = 0; i < OtherComp->GetNumChildrenComponents(); i++) {
		hitVodget = Cast<UVodget>(OtherComp->GetChildComponent(i));

		// Only consider volumes with vodgets
		if (hitVodget != nullptr && hitVodget == focusVodget) {
			if (focus_grabbed) {
				focusWillBeLostOnRelease = true;
				//UE_LOG(LogTemp, Warning, TEXT("Exited when grabbed:%s"), *FString(focusVodget->GetOwner()->GetActorLabel()));

			}
			else {
				// Leaving current focus vodget
				focusVodget->Focus(this, false);
				//UE_LOG(LogTemp, Warning, TEXT("Focus FALSE:%s"), *FString(focusVodget->GetOwner()->GetActorLabel()));
				focusVodget = nullptr;
			}
			//UE_LOG(LogTemp, Warning, TEXT("OnOverlapEnd:%s"), *FString(OtherActor->GetActorLabel()));
		}
	}
}

void UDirectSelector::GrabFocus(bool val)
{
	focus_grabbed = val;

	// If focus grab is being released and we exited the focusVodget while grabbed
	// release the current focusVodget, otherwise our cursor is still overlapping focusVodget
	// and nothing needs to be changed.
	if (!focus_grabbed && focusWillBeLostOnRelease)
	{
		// Leaving current focus vodget
		focusVodget->Focus(this, false);
		//UE_LOG(LogTemp, Warning, TEXT("Focus FALSE:%s"), *FString(focusVodget->GetOwner()->GetActorLabel()));
		focusVodget = nullptr;
	}
}