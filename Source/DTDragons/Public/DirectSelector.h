#pragma once

#include "CoreMinimal.h"
#include "Selector.h"
#include "DirectSelector.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DTDRAGONS_API UDirectSelector : public USelector {
	GENERATED_BODY()
	
	public:
		UDirectSelector();

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "VAR")
		USceneComponent *marker = nullptr;


	protected:
		virtual void SetCursor() override;

		virtual void BeginPlay() override;

		virtual void GrabFocus(bool) override;

		UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

		UFUNCTION()
		void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

		bool focusWillBeLostOnRelease = false;
};