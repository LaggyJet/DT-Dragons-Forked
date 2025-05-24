// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Grabber.h"
#include "Components/SphereComponent.h"
#include "TacVodget.h"
#include "Snapper.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DTDRAGONS_API USnapper : public USceneComponent
{
	GENERATED_BODY()


public:
	void Init(USceneComponent* owner, USphereComponent* snapCollider, UTacVodget* parentVodget, bool selfDestruct);
	void Orient();
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	void Snap(UPrimitiveComponent* OtherComp);
	void UnSnap();

	USceneComponent* owner = nullptr;
	UTacVodget* parentVodget = nullptr;
	USphereComponent* snapCollider = nullptr;
	USphereComponent* snappedTo = nullptr;

	bool canSnap = true;
	bool isSnapped = false;
	bool isOriented = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SNAP")
	bool destructChildren = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SNAP")
	bool selfDestruct = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SNAP")
	TArray<USceneComponent*> destroyOnSnap;
private:
	FString* occupyName = nullptr;
	FString* resetName = nullptr;
};
