#pragma once

#include "Selector.h"
#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Vodget.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DTDRAGONS_API UVodget : public USceneComponent {
	GENERATED_BODY()

	public:
		UVodget();

		virtual void Focus(USelector* cursor, bool state);
		virtual void ForePinch(USelector* cursor, bool state);
		virtual void MiddlePinch(USelector* cursor, bool state);
		virtual void Grip(USelector* cursor, bool state);

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Haptic Feedback")
		USoundBase* AudioFeedbackSound = nullptr;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Haptic Feedback")
		UHapticFeedbackEffect_Base* HapticEffect = nullptr;

	protected:
		virtual void BeginPlay() override;
		USceneComponent* clientComponent = nullptr;
};