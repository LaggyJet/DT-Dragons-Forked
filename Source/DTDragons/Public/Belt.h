// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Belt.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DTDRAGONS_API UBelt : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBelt();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "BELT")
	USceneComponent* camera = nullptr;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "BELT")
	float heightOffset = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "BELT")
	float forwardOffset = 0;

	USceneComponent* beltRoot = nullptr;
	FVector beltLoc;
	FVector beltOffset;
	FQuat beltRot;

	
};
