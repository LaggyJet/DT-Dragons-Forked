#pragma once

#include "CoreMinimal.h"
#include "TacVodget.h"
#include "Stabber.h"
#include "Snapper.h"
#include "MeleeVodget.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DTDRAGONS_API UMeleeVodget : public UTacVodget {
	GENERATED_BODY()
	
	public:
		virtual void Focus(USelector* selector, bool state) override;
		virtual void Grip(USelector* cursor, bool state) override;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MELEE")
		UStabber* stabber = nullptr;
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MELEE")
		USnapper* snapper = nullptr;
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MELEE")
		float disconnectDist = 1.5f;

	protected:
		USelector* grabbingSelector = nullptr;
		FTransform childsrt;

		virtual void BeginPlay() override;
		virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
};
