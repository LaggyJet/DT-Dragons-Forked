#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MRUtilityKitSubsystem.h"
#include "HAL/Runnable.h"
#include "HAL/RunnableThread.h"
#include "GameManager.generated.h"


UCLASS(Blueprintable)
class DTDRAGONS_API UGameManager : public UGameInstance {
	GENERATED_BODY()
	
	public:
		UFUNCTION(BlueprintCallable, Category = "GameManager")
		void StartWaveSpawning();

		UFUNCTION(BlueprintCallable, Category = "GameManager")
		void UpdateScore(int points);

		UFUNCTION(BlueprintCallable, Category = "GameManager")
		void UpdateEnemyCount(int killedEnemies);

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameManager")
		TArray<TSubclassOf<AActor>> EnemyBlueprints;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameManager")
		TSubclassOf<AActor> BossDragonBlueprint;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameManager")
		UMRUKSubsystem *MRUKSubsystem = nullptr;

		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GameManger")
		int currentScore = 0;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameManger")
		bool bossSpawned = false;

	protected:
		virtual void Init() override;
		virtual void Shutdown() override;

	private:
		static FTransform GetRandomNavigableLocation(UObject* WorldContextObject, const FVector& Origin, float Radius);
		void SpawnNextWave();
		void SpawnWaves();
		
		UFUNCTION()
		void SpawnNextEnemy(TSubclassOf<AActor> enemy);
		
		
		void SpawnEnemy(TSubclassOf<AActor> enemy);
		void SpawnBoss();
		bool Tick(float DeltaTime);

		int currentWave = 0, curEnemies = 0, enemiesKilled = 0, enemyThreshold = 0, roundEnemies = 0, lastWave = 0;
		float start = 0.0f, waveStartTime = 0.0f, multiplier;
		FTimerHandle WaveSpawnTimerHandle;
		FTSTicker::FDelegateHandle TickHandle;
		 
		bool debug = false; 
		bool isWaveActive = false;
};