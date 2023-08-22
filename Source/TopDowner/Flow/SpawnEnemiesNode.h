// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/FlowNode.h"
#include "TopDowner/GAS/TopDownerGameplayEffect.h"
#include "SpawnEnemiesNode.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UEnemySpawnerInterface : public UInterface
{
	GENERATED_BODY()
};

class IEnemySpawnerInterface
{    
	GENERATED_BODY()

public:	
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category=Spawning)
	void SetEnemyToSpawn(TSubclassOf<class AEnemyRobot> RobotClass);
	
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category=Spawning)
	void SetUniqueEffect(TSubclassOf<UTopDownerGameplayEffect> UniqueEffect);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category=Spawning)
	void SetUniqueFlowTag(FGameplayTagContainer UniqueEffect);

	UFUNCTION(BlueprintImplementableEvent, Category=Spawning)
	class AEnemyRobot* GetSpawnedEnemy();
	/** Add interface function declarations here */
};

/**
 * 
 */
UCLASS()
class TOPDOWNER_API USpawnEnemiesNode : public UFlowNode
{
	GENERATED_BODY()

public:
	USpawnEnemiesNode();
	
	UPROPERTY(EditAnywhere)
	FGameplayTagContainer SpawnerIdentityTags;
	
	UPROPERTY(EditAnywhere)
	EGameplayContainerMatchType MatchType {EGameplayContainerMatchType::All};

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> EnemySpawner;
	
	UPROPERTY(EditAnywhere, Category = "Spawning")
	TMap<TSubclassOf<class AEnemyRobot>, int> EnemiesToSpawn;

	UPROPERTY()
	TSet<class AEnemyRobot*> SpawnedEnemies;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UTopDownerGameplayEffect> EffectToGive;

	UPROPERTY(EditAnywhere)
	FGameplayTagContainer FlowTagsToGive;
	
	UPROPERTY(EditAnywhere, Category = "Spawning")
	float DelayBetweenSpawns;

	UFUNCTION()
	void RemoveEnemyFromSpawned(class AEnemyRobot* Robot);
	
	virtual void ExecuteInput(const FName& PinName) override;

	void FinishSpawning();
	
#if WITH_EDITOR
public:
	virtual FString GetNodeDescription() const override;
	virtual EDataValidationResult ValidateNode() override;
#endif
};
