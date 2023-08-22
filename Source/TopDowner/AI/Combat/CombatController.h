// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TopDowner/EnemyEnums.h"
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
	virtual bool ActivateLow_Implementation(){return false;}
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="CombatAI")
	bool ActivateHigh();
	virtual bool ActivateHigh_Implementation(){return false;}
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="CombatAI")
	bool ActivateNone();
	virtual bool ActivateNone_Implementation(){return false;}
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
	void AddGroupToCombat(class AEnemyGroup* NewRobot);
	UFUNCTION(BlueprintCallable)
	void RemoveGroupFromCombat(class AEnemyGroup* NewRobot);

	UFUNCTION(BlueprintPure)
	AEnemyGroup* GetUnactivatedGroup();

	UFUNCTION(BlueprintPure)
	AEnemyGroup* GetBoredGroup();
	UFUNCTION()
	void TimerOnBoredomEnded(class AEnemyGroup* Group);
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	class AEnemyGroup* FindNearestAcceptableGroup(class AEnemyRobot* Enemy);
	
	UFUNCTION(BlueprintCallable)
	void AddEnemyToCombat(class AEnemyRobot* NewRobot);
	UFUNCTION(BlueprintCallable)
	void AddRequiredEnemyToCombat(class AEnemyRobot* NewRobot);

	UFUNCTION(BlueprintCallable)
	void RemoveEnemyFromCombat(class AEnemyRobot* NewRobot);

	virtual void Tick(float DeltaSeconds) override;
	
	// UFUNCTION(BlueprintCallable)
	// void ActivateEnemyHigh();
	// UFUNCTION(BlueprintCallable)
	// void ActivateEnemyLow();

	//Single Unit Controls
	UFUNCTION(BlueprintCallable, BlueprintPure)
	class AEnemyRobot* GetRandomUnactiveEnemy(TEnumAsByte<EEnemyType> EnemyType) const;
	UFUNCTION(BlueprintCallable, BlueprintPure)
	class AEnemyRobot* GetRandomUnactiveBasicEnemy() const;
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetNumberOfBasicEnemies();
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetNumberOfActiveBasicEnemies();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	class AEnemyRobot* GetRandomUnactiveSpecialEnemy() const;
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetNumberOfSpecialEnemies();
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetNumberOfActiveSpecialEnemies();

	UFUNCTION()
	void ReactToEnemyActivatedLow(class AEnemyRobot* Enemy);
	UFUNCTION()
	void ReactToEnemyActivatedHigh(class AEnemyRobot* Enemy);
	UFUNCTION()
	void ReactToEnemyDeactivated(class AEnemyRobot* Enemy);
	UFUNCTION()
	void ReactToEnemyDied(class AEnemyRobot* Enemy);
	
protected:
	UPROPERTY()
	TMap<UClass*, int> EnemiesAmounts;

	void AddEnemyToAmountMap(class AEnemyRobot* NewRobot);
	void RemoveEnemyRobotFromAmountMap(class AEnemyRobot* NewRobot);

	UPROPERTY()
	UBehaviorTree* CombatTree;

	UPROPERTY(BlueprintReadOnly)
	TArray<class AEnemyGroup *> GroupsInCombat;

	UPROPERTY(BlueprintReadOnly)
	TArray<class AEnemyGroup *> BoredGroups;

	//TODO turn to sets?
	UPROPERTY()
	TSet<class AEnemyRobot*> AllEnemiesInCombat;
	UPROPERTY()
	TArray<class AEnemyRobot*> NotActiveEnemiesInCombat;
	UPROPERTY()
	TArray<class AEnemyRobot*> LowActiveEnemiesInCombat;
	UPROPERTY()
	TArray<class AEnemyRobot*> HighActiveEnemiesInCombat;

	UPROPERTY()
	TArray<class AEnemyRobot*> AllEnemiesInCombatRequired;
};
