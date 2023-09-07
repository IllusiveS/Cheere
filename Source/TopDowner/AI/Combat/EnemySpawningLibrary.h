// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TopDowner/GAS/TopDownerGameplayEffect.h"
#include "EnemySpawningLibrary.generated.h"

USTRUCT(BlueprintType)
struct FEnemySpawnData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTagContainer SpawnerIdentityTags;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EGameplayContainerMatchType MatchType {EGameplayContainerMatchType::All};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> EnemySpawner;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	TMap<TSubclassOf<class AEnemyRobot>, int> EnemiesToSpawn;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UTopDownerGameplayEffect> EffectToGive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTagContainer FlowTagsToGive;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	float DelayBetweenSpawns;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	bool ShouldAutoActivate;
};

/**
 * 
 */
UCLASS()
class TOPDOWNER_API UEnemySpawningLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, meta=(HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"))
	static void SpawnEnemy(UObject* WorldContextObject, FEnemySpawnData SpawnData);
};
