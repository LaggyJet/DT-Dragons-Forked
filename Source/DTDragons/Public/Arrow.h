// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TacVodget.h"
#include "Snapper.h"
#include "Stabber.h"
#include "Arrow.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DTDRAGONS_API UArrow : public UTacVodget
{
	GENERATED_BODY()
	

public:
	
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void Grip(USelector* cursor, bool state) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ARROW")
	USceneComponent* grabCollider = nullptr;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ARROW")
	USnapper* snapper = nullptr;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ARROW")
	UStabber* stabber = nullptr;

protected:
	// Called when the game starts
	USceneComponent* parentClient = nullptr;
	USelector* grabbingSelector = nullptr;
	FTransform childsrt;
	bool drawn = false;

	float initPos;
	float testPos;

	float minval = -57.0;
	float maxval = 0.0;
};
