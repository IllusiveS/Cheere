// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HackingSequenceObject.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHackingCallback);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FHackingAmmountCallback, float, HackingAmmount, float, MaxHackingAmmount);

/**
 * 
 */
UCLASS()
class TOPDOWNER_API UHackingSequenceObject : public UObject
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
	
	void BeginHacking();
	void EndHacking();

	UPROPERTY(BlueprintAssignable)
	FHackingCallback OnHackingFinished;

	UPROPERTY(BlueprintAssignable)
	FHackingAmmountCallback OnHackingStatusChange;
};
