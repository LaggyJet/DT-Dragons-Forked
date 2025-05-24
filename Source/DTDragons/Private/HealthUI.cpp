// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthUI.h"

void UHealthUI::HealthPct(float pct)
{
	Health = FMath::Clamp(Health, 0.0f, 100.0f);

	if (healthIndicatorCover)
	{
		// expecting a value from 0-100
		if (pct > 1.0)
		{
			pct = pct / 100;
		}

		float minScale = 0.01f;
		float maxScale = 1.0f;

		float newScale = FMath::Lerp(minScale, maxScale, pct);
		healthIndicatorCover->SetRelativeScale3D(FVector(newScale, newScale, newScale));

		if (pct <= minScale)
		{
			healthIndicatorCover->SetVisibility(false);
		}
	}
}

//void UHealthUI::BeginPlay()
//{
//
//}




