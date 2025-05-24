#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Stabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DTDRAGONS_API UStabber : public USceneComponent {
	GENERATED_BODY()

public:	
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent *OverlappedComp, class AActor *OtherActor, class UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Haptic Feedback")
	TArray<USoundBase*> StabSound;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Stabber")
	USceneComponent *collider = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Stabber")
	int damage;

	bool canStab = false;
};
