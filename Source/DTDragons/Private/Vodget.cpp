#include "Vodget.h"
#include "Selector.h"
#include "Kismet/GameplayStatics.h"
#include "MotionControllerComponent.h"

UVodget::UVodget() {
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;
}

void UVodget::BeginPlay() {
	Super::BeginPlay();

	clientComponent = GetAttachParent();

	//clientComponent = clientComponent->GetChildComponent(0);

	if (clientComponent == nullptr)
		clientComponent = this;
}

void UVodget::ForePinch(USelector* cursor, bool state) {
	if (!cursor || !state)
		return;

	if (AudioFeedbackSound)
		UGameplayStatics::PlaySoundAtLocation(this, AudioFeedbackSound, GetComponentLocation());
	if (UMotionControllerComponent* comp = Cast<UMotionControllerComponent>(cursor->controller); comp && HapticEffect)
		if (APlayerController* PC = Cast<APlayerController>(Cast<APawn>(comp->GetOwner())->GetController()))
			PC->PlayHapticEffect(HapticEffect, comp->GetTrackingSource());
}

void UVodget::Focus(USelector* cursor, bool state) {}

void UVodget::MiddlePinch(USelector* cursor, bool state) {}

void UVodget::Grip(USelector* cursor, bool state) {}