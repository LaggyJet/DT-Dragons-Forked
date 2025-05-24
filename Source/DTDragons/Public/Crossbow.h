// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <Components/CapsuleComponent.h>
#include "CoreMinimal.h"
#include "TacVodget.h"
#include "Crossbow.generated.h"

// Define a float variable delegate that multiple blueprint clients can register callbacks for when the value changes.
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCrossbowTriggerDelegate, bool, TriggerState);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DTDRAGONS_API UCrossbow : public UTacVodget
{
	GENERATED_BODY()

public:
	virtual void ForePinch(USelector* cursor, bool state) override;
	virtual void Grip(USelector* cursor, bool state) override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	
	UPROPERTY(BlueprintAssignable, Category = "BOW")
	FCrossbowTriggerDelegate triggerDelegate;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "BOW")
	USceneComponent* turnRoot = nullptr;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "BOW")
	USceneComponent* tiltRoot = nullptr;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "BOW")
	USceneComponent* arrowRoot = nullptr;

protected:
	// Called when the game starts
	USelector* grabbingSelector = nullptr;
	FVector initYawVec;
	FVector initPitchVec;
};