#include "MeleeVodget.h"

void UMeleeVodget::BeginPlay() {
    Super::BeginPlay();
    clientComponent = GetAttachmentRoot();
    snapper->Init(clientComponent, snapJoint, this, false);
}

void UMeleeVodget::Focus(USelector* selector, bool state) {
    if (!state && selector == grabbingSelector)
        grabbingSelector = nullptr;
}

void UMeleeVodget::Grip(USelector* selector, bool state) {
    Super::Grip(selector, state);

    if (grabbingSelector && grabbingSelector != selector) {
        return;
    }

    if (snapper && snapper->isSnapped) PrimaryComponentTick.SetTickFunctionEnable(true);
    else PrimaryComponentTick.SetTickFunctionEnable(state);

    selector->GrabFocus(state);
    stabber->canStab = state;
    grabbingSelector = state ? selector : nullptr;
}

void UMeleeVodget::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
    if (snapper && snapper->isSnapped)
    {
        clientComponent->SetWorldLocationAndRotation(snapper->snappedTo->GetComponentLocation(), snapper->snappedTo->GetComponentRotation());
        snapper->canSnap = false;
        if (grabbingSelector)
        {
            FVector loc = grabbingSelector->Cursor().GetLocation();
            FVector meleeLoc = clientComponent->GetComponentLocation();
            if (FVector::Distance(loc, meleeLoc) > disconnectDist) snapper->UnSnap();
        }
    }
    else if (grabbingSelector) {
        clientComponent->SetWorldLocation(grabbingSelector->Cursor().TransformPosition(FVector(-1, 0, 5)));
        clientComponent->SetWorldRotation(grabbingSelector->Cursor().GetRotation() * FQuat(FRotator(70, 0, 0)));
        if (snapper) snapper->canSnap = true;
    }
}
