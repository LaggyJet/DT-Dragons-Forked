// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Vodget.h"
#include "SphereComponent.h"
#include "Spinner.h"
#include "TacVodget.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DTDRAGONS_API UTacVodget : public UVodget
{
	GENERATED_BODY()
	
public:
	virtual void Grip(USelector* cursor, bool state) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "TAC")
	UTacVodget* parent = nullptr;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "TAC")
	UTacVodget* child = nullptr;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "TAC")
	USphereComponent* snapJoint = nullptr;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "TAC")
	USpinner* spinner = nullptr;

	UTacVodget* GetParent() { return parent; }
	UTacVodget* GetChild() { return child; }
	void SetParent(UTacVodget* newParent) { parent = newParent; }
	void SetChild(UTacVodget* newChild) { child = newChild; }

	bool flag = false;
	bool canSnapTo = true;
};
