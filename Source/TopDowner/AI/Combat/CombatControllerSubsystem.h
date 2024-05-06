// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "CombatControllerSubsystem.generated.h"

class ACombatController;
/**
 * 
 */
UCLASS(Blueprintable)
class TOPDOWNER_API UCombatControllerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UCombatControllerSubsystem();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UBehaviorTree* CombatTree{nullptr};
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<ACombatController> CombatController;

	UFUNCTION(BlueprintCallable)
	void StartCombat(TMap<TSubclassOf<class AEnemyRobot>, int> DesiredEnemies);

	UFUNCTION()
	void EndCombat();
	
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
};

UCLASS()
class TOPDOWNER_API UCombatControllerFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Combat", meta = (WorldContext = "WorldContextObject"))
	static ACombatController* GetCombatController(const UObject* WorldContextObject);
	
};
