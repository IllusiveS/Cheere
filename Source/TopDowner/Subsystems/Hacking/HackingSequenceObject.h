// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/NoExportTypes.h"
#include "HackingSequenceObject.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHackingCallback);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FHackingAmmountCallback, float, HackingAmmount, float, MaxHackingAmmount);

/**
 * 
 */
UCLASS()
class TOPDOWNER_API AHackingSequenceObject : public AActor
{
	GENERATED_BODY()

public:
	
	UPROPERTY()
	float CurrentPoints;
	
	UPROPERTY(EditAnywhere)
	float PointsRequired;

	UPROPERTY(EditAnywhere)
	float PointsGainedPerSlotCharged;

	UPROPERTY(EditAnywhere)
	int NumberOfBatteriesToSpawn;
	
	UFUNCTION(BlueprintCallable)
	void AddBatteryPower(float PowerToAdd);

	void GatherBatterySlots(FGameplayTagContainer IdentityTags);
	void GatherBatteries(FGameplayTagContainer IdentityTags);
	void BeginHacking();
	
	
	void EndHacking();

	UPROPERTY(BlueprintReadOnly)
	TArray<AActor*> BatterySlots;

	UPROPERTY(BlueprintReadOnly)
	TArray<AActor*> Batteries;
	
	UPROPERTY(BlueprintAssignable)
	FHackingCallback OnHackingFinished;

	UPROPERTY(BlueprintAssignable)
	FHackingAmmountCallback OnHackingStatusChange;
};
