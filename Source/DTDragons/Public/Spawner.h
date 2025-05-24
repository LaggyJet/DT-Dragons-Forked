// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Spawner.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DTDRAGONS_API USpawner : public UActorComponent
{
	GENERATED_BODY()
	USpawner();

public:	
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SPAWN")
	USceneComponent* gunSpawnPnt;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SPAWN")
	USceneComponent* knifeSpawnPnt;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SPAWN")
	TSubclassOf<AActor> gunBP;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SPAWN")
	TSubclassOf<AActor> knifeBP;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
		
};
