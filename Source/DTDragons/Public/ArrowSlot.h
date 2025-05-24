// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TacVodget.h"
#include "ArrowSlot.generated.h"


/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DTDRAGONS_API UArrowSlot : public UTacVodget
{
	GENERATED_BODY()

public:
	virtual void Grip(USelector* cursor, bool state) override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SLOT")
	UTacVodget* owner = nullptr;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SLOT")
	USceneComponent* connectJoint = nullptr;

protected:
	// Called when the game starts
	USelector* grabbingSelector = nullptr;
	bool drawn = false;
	
	float initPos;
	float testPos;

	float minval = -57.0;
	float maxval = 0.0;
};
