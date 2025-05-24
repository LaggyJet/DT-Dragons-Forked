// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "WristUIComponent.generated.h"


/**
 * 
 */
UCLASS()
class DTDRAGONS_API UWristUIComponent : public UWidgetComponent
{
	GENERATED_BODY()

private:


public:
	UWristUIComponent();

	UFUNCTION(BlueprintCallable, Category = "WristUI")
	void AttachToHand(USkeletalMeshComponent* HandMesh, FName SocketName = TEXT("WristSocket"));

	/** Set the UI Widget Class dynamically */
	UFUNCTION(BlueprintCallable, Category = "WristUI")
	void UpdateWristUI(TSubclassOf<UUserWidget> NewWidgetClass);

protected:
	virtual void BeginPlay() override;

	/** Stores the Widget Blueprint class */
	UPROPERTY(EditAnywhere, Category = "WristUI")
	TSubclassOf<UUserWidget> WristUIClass;
	
};
