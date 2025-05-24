// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TacVodget.h"
#include "Snapper.h"
#include "Gun.generated.h"

/**
 * 
 */
 // Define a float variable delegate that multiple blueprint clients can register callbacks for when the value changes.
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGunTriggerDelegate, bool, TriggerState);
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DTDRAGONS_API UGun : public UTacVodget
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void ForePinch(USelector* cursor, bool state) override;
	virtual void Grip(USelector* cursor, bool state);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GUN")
	USceneComponent* offset = nullptr;

	UPROPERTY(BlueprintAssignable, Category = "GUN")
	FGunTriggerDelegate triggerDelegate;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GUN")
	USnapper* snapper = nullptr;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GUN")
	float disconnectDist = 1.5f;

protected:
	// Called when the game starts
	USelector* grabbingSelector = nullptr;
	bool isDocked = false;
	FTransform childsrt;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UVodget* child = nullptr;

	
};