// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HealthUI.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DTDRAGONS_API UHealthUI : public USceneComponent
{

	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Health")
	void HealthPct(float pct);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Health")
	USceneComponent* healthIndicator;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Health")
	USceneComponent* healthIndicatorCover;

	//UFUNCTION(BlueprintCallable, Category = "StrutAssembly")
	//void MaxHealth(float deg);

protected:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Health")
	float Health = 100.0f;

	//virtual void BeginPlay() override;
};