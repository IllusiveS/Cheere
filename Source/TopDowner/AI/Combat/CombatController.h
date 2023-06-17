// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CombatController.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UAICombatInterface : public UInterface
{
	GENERATED_BODY()
};

class IAICombatInterface
{    
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="CombatAI")
	bool ActivateLow();
	bool ActivateLow_Implementation(){return false;}
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="CombatAI")
	bool ActivateHigh();
	bool ActivateHigh_Implementation(){return false;}
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="CombatAI")
	bool ActivateNone();
	bool ActivateNone_Implementation(){return false;}
};

/**
 * 
 */
UCLASS()
class TOPDOWNER_API ACombatController : public AAIController
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void BeginCombat();

	UFUNCTION(BlueprintCallable)
	void EndCombat();

	UFUNCTION(BlueprintCallable)
	void AddEnemyToCombat(class AEnemyRobot* NewRobot);
	UFUNCTION(BlueprintCallable)
	void AddRequiredEnemyToCombat(class AEnemyRobot* NewRobot);

	UFUNCTION(BlueprintCallable)
	void RemoveEnemyFromCombat(class AEnemyRobot* NewRobot);

	
	// UFUNCTION(BlueprintCallable)
	// void ActivateEnemyHigh();
	// UFUNCTION(BlueprintCallable)
	// void ActivateEnemyLow();
	
protected:
	UPROPERTY()
	TMap<UClass*, int> EnemiesAmounts;

	void AddEnemyToAmountMap(class AEnemyRobot* NewRobot);
	void RemoveEnemyRobotFromAmountMap(class AEnemyRobot* NewRobot);

	UPROPERTY()
	UBehaviorTree* CombatTree;
	
	UPROPERTY()
	TArray<class AEnemyRobot*> AllEnemiesInCombat;
	UPROPERTY()
	TArray<class AEnemyRobot*> NotActiveEnemiesInCombat;
	UPROPERTY()
	TArray<class AEnemyRobot*> LowActiveEnemiesInCombat;
	UPROPERTY()
	TArray<class AEnemyRobot*> HighActiveEnemiesInCombat;

	UPROPERTY()
	TArray<class AEnemyRobot*> AllEnemiesInCombatRequired;
};