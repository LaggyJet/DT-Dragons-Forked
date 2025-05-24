#include "Selector.h"
#include "Vodget.h"
#include "MotionControllerComponent.h"

USelector::USelector() { PrimaryComponentTick.bCanEverTick = true; }

void USelector::ForePinch(const bool Value) {
	if (focusVodget != nullptr)
		focusVodget->ForePinch(this, Value);
}
void USelector::MiddlePinch(const bool Value) {
	if (focusVodget != nullptr)
		focusVodget->MiddlePinch(this, Value);
}
void USelector::Grip(const bool Value) {
	if (focusVodget != nullptr)
		focusVodget->Grip(this, Value);
}

const FTransform& USelector::Cursor() {
	SetCursor();
	return cursor;
}

void USelector::SetCursor() {}