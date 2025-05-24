#include "FloorCollider.h"

void UFloorCollider::BeginPlay() {
	Super::BeginPlay();
	if (floor) {
		if (UStaticMeshComponent* meshComp = Cast<UStaticMeshComponent>(floor)) {
			meshComp->SetGenerateOverlapEvents(true);
			meshComp->OnComponentBeginOverlap.AddDynamic(this, &UFloorCollider::OnOverlapBegin);
			meshComp->OnComponentEndOverlap.AddDynamic(this, &UFloorCollider::OnOverlapEnd);
		}
	}
}

void UFloorCollider::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
    if (OtherComp)
        if (UPrimitiveComponent* PrimitiveComp = Cast<UPrimitiveComponent>(OtherComp))
			PrimitiveComp->SetEnableGravity(false);
}

void UFloorCollider::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
    if (OtherComp)
        if (UPrimitiveComponent* PrimitiveComp = Cast<UPrimitiveComponent>(OtherComp))
            PrimitiveComp->SetEnableGravity(true);
}
