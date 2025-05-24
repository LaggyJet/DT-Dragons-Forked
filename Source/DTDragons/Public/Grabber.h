#pragma once

#include "CoreMinimal.h"
#include "Vodget.h"
#include "Grabber.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DTDRAGONS_API UGrabber : public UVodget {
	GENERATED_BODY()

	public:
		virtual void Focus(USelector* selector, bool state) override;
		virtual void Grip(USelector* cursor, bool state) override;

	protected:
		USelector* grabbingSelector = nullptr;
		FTransform childsrt;

		virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
};