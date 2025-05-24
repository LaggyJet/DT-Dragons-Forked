#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "DTPawn.generated.h"

UCLASS()
class DTDRAGONS_API ADTPawn : public APawn {
	GENERATED_BODY()	

	public:
		ADTPawn();

	protected:
		UPROPERTY(BlueprintReadWrite)
		class USceneComponent* CameraRig;

		UPROPERTY(BlueprintReadOnly)
		class UCameraComponent* Camera;

		UPROPERTY(BlueprintReadOnly)
		class UMotionControllerComponent* RightMotionController;

		UPROPERTY(BlueprintReadOnly)
		class UMotionControllerComponent* LeftMotionController;

		class USelector* lselector;
		class USelector* rselector;
};