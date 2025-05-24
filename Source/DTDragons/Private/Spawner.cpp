// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner.h"
#include "Gun.h"
#include "MeleeVodget.h"
#include "Snapper.h"
#include "Components/SceneComponent.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/Actor.h"

USpawner::USpawner() {}

// Called when the game starts
void USpawner::BeginPlay()
{
	Super::BeginPlay();

	//! 1 : Spawning the gun and knife and saving a pointer to their actors
	AActor* gunActor = nullptr;
	AActor* knifeActor = nullptr;
	TArray<USceneComponent*> gunChildren;
	TArray<USceneComponent*> knifeChildren;

	UWorld* World = GetWorld();
	FActorSpawnParameters SpawnParams;
	if (gunBP)
	{
		if (World)
		{
			FVector SpawnLocation = gunSpawnPnt->GetComponentLocation();
			FRotator SpawnRotation = gunSpawnPnt->GetComponentRotation();

			gunActor = World->SpawnActor<AActor>(gunBP, SpawnLocation, SpawnRotation, SpawnParams);
		}
	}
	if (knifeBP)
	{
		if (World)
		{
			FVector SpawnLocation = knifeSpawnPnt->GetComponentLocation();
			FRotator SpawnRotation = knifeSpawnPnt->GetComponentRotation();

			knifeActor = World->SpawnActor<AActor>(knifeBP, SpawnLocation, SpawnRotation, SpawnParams);
		}
	}

	//! 2 : Gets all the components of our actors and looks for their vodget and their snapper in order to start ticking on the vodget then forcibly snap them to the holster
	if (gunActor) 
	{
		gunActor->InitializeComponents();
		gunActor->GetComponents<USceneComponent>(gunChildren);
		for (int i = 0; i < gunChildren.Num(); i++)
		{
			UGun* temp = Cast<UGun>(gunChildren[i]);
			if (temp)
				temp->SetComponentTickEnabled(true);
			else
			{
				USnapper* temp2 = Cast<USnapper>(gunChildren[i]);
				if (temp2)
				{
					UPrimitiveComponent* temp3 = Cast<UPrimitiveComponent>(gunSpawnPnt);
					if (temp3) temp2->Snap(temp3);
				}
			}
		}
	}
	if (knifeActor)
	{
		knifeActor->InitializeComponents();
		knifeActor->GetComponents<USceneComponent>(knifeChildren);
		for (int i = 0; i < knifeChildren.Num(); i++)
		{
			UMeleeVodget* temp = Cast<UMeleeVodget>(knifeChildren[i]);
			if (temp)
				temp->SetComponentTickEnabled(true);
			else
			{
				USnapper* temp2 = Cast<USnapper>(knifeChildren[i]);
				if (temp2)
				{
					UPrimitiveComponent* temp3 = Cast<UPrimitiveComponent>(knifeSpawnPnt);
					if (temp3) temp2->Snap(temp3);
				}
			}
		}
	}
}