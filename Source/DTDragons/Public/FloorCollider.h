#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "FloorCollider.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DTDRAGONS_API UFloorCollider : public USceneComponent {
	GENERATED_BODY()

	public:
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Floor Collider")
		USceneComponent *floor = nullptr;

	protected:
		virtual void BeginPlay() override;
		
		UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

		UFUNCTION()
		void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
