#include "GameManager.h"
#include "NavigationSystem.h"
#include "MRUtilityKit.h"
#include "MRUtilityKitAnchor.h"
#include "Kismet/GameplayStatics.h"

void UGameManager::Init() {
	Super::Init();
	TickHandle = FTSTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateUObject(this, &UGameManager::Tick), 0.5f);
	start = GetWorld()->GetRealTimeSeconds();
}

void UGameManager::Shutdown() {
	Super::Shutdown();
	FTSTicker::GetCoreTicker().RemoveTicker(TickHandle);
}

bool UGameManager::Tick(float DeltaTime) {
	if (curEnemies == 0 && isWaveActive) {
		GetWorld()->GetTimerManager().ClearTimer(WaveSpawnTimerHandle);
		SpawnNextWave();
	}

	if (GetWorld()->GetRealTimeSeconds() <= 60)
		multiplier = 2;
	else if (GetWorld()->GetRealTimeSeconds() >= 540)
		multiplier = 0.5;
	else
		multiplier = FMath::Lerp(2.0f, 0.5f, ((GetWorld()->GetRealTimeSeconds() - start) - 60) / 480.0f);
	return true;
}

void UGameManager::StartWaveSpawning() {
	currentWave = 1;
	if (!debug)
		SpawnNextWave();
	else
		SpawnBoss();
}

void UGameManager::UpdateScore(int points) { currentScore += (points * multiplier); }

void UGameManager::UpdateEnemyCount(int killedEnemies) { 
	curEnemies -= killedEnemies; 
	enemiesKilled += killedEnemies;
}

void UGameManager::SpawnNextWave() {
	if (currentWave == 6) SpawnBoss();
	else if (currentWave > 6) return;
	else if (currentWave != lastWave) SpawnWaves();
	GetWorld()->GetTimerManager().SetTimer(WaveSpawnTimerHandle, this, &UGameManager::SpawnNextWave, 30.0f, false);
}

FTransform UGameManager::GetRandomNavigableLocation(UObject* WorldContextObject, const FVector& Origin, float Radius) {
	if (!WorldContextObject) 
		return FTransform::Identity;
	UNavigationSystemV1* NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(WorldContextObject);
	if (!NavSystem) 
		return FTransform::Identity;
	FNavLocation RandomLocation;
	if (NavSystem->GetRandomReachablePointInRadius(Origin, Radius, RandomLocation))
		return FTransform(RandomLocation.Location);
	return FTransform::Identity;
}

void UGameManager::SpawnWaves() { 
	if (EnemyBlueprints.Num() == 0) 
		return; 
	lastWave = currentWave;
	isWaveActive = true;
	roundEnemies = 0;
	enemiesKilled = 0;
	waveStartTime = GetWorld()->GetRealTimeSeconds();
	enemyThreshold = 1 + (currentWave * 2);
	if(roundEnemies < enemyThreshold) SpawnNextEnemy(EnemyBlueprints[FMath::RandHelper(EnemyBlueprints.Num())]);
}

void UGameManager::SpawnNextEnemy(TSubclassOf<AActor> enemy) {
	if (enemiesKilled >= enemyThreshold) {
		currentWave++;
		isWaveActive = false;
		return;
	}
	else if (roundEnemies < enemyThreshold) {
		SpawnEnemy(enemy);
		float baseDelay = 1.0f;
		float waveRatio = 5.0f / currentWave; //five could be replaced by max wave if that change is implemented
		float spawnDelay = baseDelay * waveRatio;
		FMath::SRandInit(FMath::Rand());
		float randomizer = FMath::SRand();
		spawnDelay *= randomizer;
		FTimerDelegate Delegate;
		Delegate.BindUFunction(this, FName("SpawnNextEnemy"), enemy);
		FTimerHandle UnusedHandle;
		GetWorld()->GetTimerManager().SetTimer(UnusedHandle, Delegate, spawnDelay, false);
	}
	else 
		currentWave++;
}


void UGameManager::SpawnEnemy(TSubclassOf<AActor> enemy) {
	FVector playerLocation = UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->GetActorLocation();
	playerLocation.Z = MRUKSubsystem->GetCurrentRoom()->FloorAnchor->GetActorLocation().Z + 2.0f;
	FActorSpawnParameters spawnParams;
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	GetWorld()->SpawnActor<AActor>(enemy, GetRandomNavigableLocation(this, playerLocation, 2000), spawnParams);
	curEnemies++;
	roundEnemies++;
}

// Kheera's testing function 

//void UGameManager::SpawnEnemy(TSubclassOf<AActor> enemy) {
//	FVector playerLocation = UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->GetActorLocation(); 
//
//	// Floor Z override (keep their logic) 
//	playerLocation.Z = MRUKSubsystem->GetCurrentRoom()->FloorAnchor->GetActorLocation().Z + 2.0f; 
//
//	// Grab nav location
//	FVector spawnLoc = GetRandomNavigableLocation(this, playerLocation, 2000).GetLocation(); 
//
//	// Add random XY scatter
//	spawnLoc.X += FMath::RandRange(-300.0f, 300.0f); 
//	spawnLoc.Y += FMath::RandRange(-300.0f, 300.0f); 
//	spawnLoc.Z += 100.0f; // Raise off floor a bit more just in case 
//
//	FActorSpawnParameters spawnParams; 
//	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn; 
//
//	GetWorld()->SpawnActor<AActor>(enemy, spawnLoc, FRotator::ZeroRotator, spawnParams); 
//	curEnemies++; 
//}



void UGameManager::SpawnBoss() {
	bossSpawned = true;
	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), "RubbleSpawn", actors);
	FActorSpawnParameters spawnParams;
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	for (AActor* actor : actors)
		GetWorld()->SpawnActor<AActor>(BossDragonBlueprint, actor->GetActorTransform() + FTransform(FVector(0.0f, 0.0f, 30000.0f)), spawnParams);
	currentWave++;
}