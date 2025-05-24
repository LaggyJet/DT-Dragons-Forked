// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DirectSelector.h"
#include "TacSelector.generated.h"

/**
//! This Class is unused as of 3/4/2025
//! Kept here in case changes need to be made to the selector
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DTDRAGONS_API UTacSelector : public UDirectSelector
{
	GENERATED_BODY()
	

public:
	void ReplaceFocusVodget(UVodget* vodget);
};
