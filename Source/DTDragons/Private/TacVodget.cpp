// Fill out your copyright notice in the Description page of Project Settings.


#include "TacVodget.h"

void UTacVodget::Grip(USelector* cursor, bool state)
{
	if (spinner) 
	{
		spinner->spin = !state;
		//spinner->PrimaryComponentTick.SetTickFunctionEnable(state);
	}
}
