#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Selector.generated.h"

class UVodget;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DTDRAGONS_API USelector : public UActorComponent {
	GENERATED_BODY()

	public:
		USelector();



		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "VAR")
		USceneComponent* controller = nullptr;

		virtual void GrabFocus(bool val) { focus_grabbed = val; }

		const FTransform& Cursor();

		UFUNCTION(BlueprintCallable, Category = "VAR")
		void ForePinch(const bool Value);

		UFUNCTION(BlueprintCallable, Category = "VAR")
		void MiddlePinch(const bool Value);

		UFUNCTION(BlueprintCallable, Category = "VAR")
		void Grip(const bool Value);

	protected:
		virtual void SetCursor();
		FTransform cursor;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "VAR")
		UVodget* focusVodget = nullptr;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "VAR")
		bool focus_grabbed = false;
};