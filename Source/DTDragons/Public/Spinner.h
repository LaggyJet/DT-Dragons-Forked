// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "PointLightComponent.h"
#include "Spinner.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DTDRAGONS_API USpinner : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USpinner();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SPIN")
	USceneComponent* root = nullptr;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SPIN")
	int verticalOffset = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SPIN")
	UPointLightComponent* glowLight = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SPIN")
	USoundBase* audioEmissionSound = nullptr;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	bool spin = true;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SPIN")
	bool glow = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SPIN")
	bool emitSound = false;
		
};
