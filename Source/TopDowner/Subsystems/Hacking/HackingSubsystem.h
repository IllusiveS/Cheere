// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "HackingSequenceObject.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "HackingSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHackingObjectChange, AHackingSequenceObject*, Object);

USTRUCT(Blueprintable)
struct FHackingStartStructData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	float PointsRequired;

	UPROPERTY(EditAnywhere)
	float PointsGainedPerSlotCharged;

	UPROPERTY(EditAnywhere)
	int NumberOfBatteriesToSpawn;

	UPROPERTY(EditAnywhere)
	FGameplayTagContainer BatterySlotsIdentityTags;
	
	UPROPERTY(EditAnywhere)
	FGameplayTagContainer BatteryIdentityTags;
};

/**
 * 
 */
UCLASS()
class TOPDOWNER_API UHackingSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	AHackingSequenceObject* CurrentCombat;

	UFUNCTION(BlueprintCallable)
	void PrepareHacking(UWorld* world, FHackingStartStructData Data);
	
	UFUNCTION(BlueprintCallable)
	void BeginHacking();

	UFUNCTION(BlueprintCallable)
	void FinishHacking();

	UPROPERTY(BlueprintAssignable)
	FOnHackingObjectChange OnHackingBegin;

	UPROPERTY(BlueprintAssignable)
	FOnHackingObjectChange OnHackingEnd;
};
