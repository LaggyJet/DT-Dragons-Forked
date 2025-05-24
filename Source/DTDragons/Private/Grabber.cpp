#include "Grabber.h"

void UGrabber::Focus(USelector* selector, bool state) { 
    if (!state && selector == grabbingSelector) 
        grabbingSelector = nullptr;
}

void UGrabber::Grip(USelector* selector, bool state) {
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
    if (state) {
        // Save the grabbing selector.
        grabbingSelector = selector;

        // Set childsrt(rotation/location/scale)  to the       clients transform        as a child       of the     selectors cursor.
        childsrt = clientComponent->GetComponentTransform() * selector->Cursor().Inverse();

        PrimaryComponentTick.SetTickFunctionEnable(true);
    }
    else {
        // Clear the grabbing selector.
        grabbingSelector = nullptr;
        PrimaryComponentTick.SetTickFunctionEnable(false);
    }
}

void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) { 
    if (grabbingSelector)
    {
        FTransform newT = (childsrt * grabbingSelector->Cursor());
        clientComponent->SetWorldTransform(newT);
        clientComponent->SetWorldRotation(newT.GetRotation());
    }
}
