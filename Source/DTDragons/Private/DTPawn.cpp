#include "DTPawn.h"
#include "Selector.h"
#include "Components/SceneComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "MotionControllerComponent.h"

ADTPawn::ADTPawn() {
	PrimaryActorTick.bCanEverTick = true;

	CameraRig = CreateDefaultSubobject<USceneComponent>(TEXT("CameraRig"));
	this->SetRootComponent(CameraRig);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraRig);

	LeftMotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("LeftMotionController"));
	LeftMotionController->SetTrackingSource(EControllerHand::Left);
	LeftMotionController->SetupAttachment(CameraRig);

	RightMotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("RightMotionController"));
	RightMotionController->SetTrackingSource(EControllerHand::Right);
	RightMotionController->SetupAttachment(CameraRig);
}