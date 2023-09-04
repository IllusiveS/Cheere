// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/FlowNode.h"
#include "HackingSequence.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNER_API UHackingSequence : public UFlowNode
{
	GENERATED_BODY()

public:
	UHackingSequence();

	UPROPERTY(EditAnywhere)
	float PointsRequired;

	UPROPERTY(EditAnywhere)
	float PointsGainedPerSlotCharged;

	UPROPERTY(EditAnywhere)
	int NumberOfBatteriesToSpawn;

	UPROPERTY(EditAnywhere)
	FGameplayTagContainer BatterySlotsIdentityTags;
	
	UPROPERTY(EditAnywhere)
	FGameplayTagContainer BatterySpawnPointsIdentityTags;

	virtual void ExecuteInput(const FName& PinName) override;

	UFUNCTION()
	void OnHackingDone();
};
