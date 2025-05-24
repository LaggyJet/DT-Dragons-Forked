#include "Stabber.h"
#include "SphereComponent.h"
#include "Kismet/GameplayStatics.h"

void UStabber::BeginPlay() {
	Super::BeginPlay();
	if (collider) {
		if (USphereComponent *sphereCol = Cast<USphereComponent>(collider)) {
			sphereCol->SetGenerateOverlapEvents(true);
			sphereCol->OnComponentBeginOverlap.AddDynamic(this, &UStabber::OnOverlapBegin);
		}
	}
}

void UStabber::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (!canStab || !OtherActor) return;
	if (OtherActor->GetClass()->GetSuperClass()->GetName().Equals("BP_EnemyPawn_C")) {
		if (UFunction* Function = OtherActor->FindFunction(FName("TakeDamage"))) {
			OtherActor->ProcessEvent(Function, &damage);
			if (!StabSound.IsEmpty())
				UGameplayStatics::PlaySoundAtLocation(this, StabSound[FMath::RandHelper(StabSound.Num())], GetComponentLocation());
		}
	}
}