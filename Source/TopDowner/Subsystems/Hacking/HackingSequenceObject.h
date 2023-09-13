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

	UFUNCTION(BlueprintPure)
	class ABatteryOnGround* GetBatteryToSteal();
	
	void EndHacking();

	UFUNCTION()
	void ReactToBatteryStateChange(class ABatteryOnGround* Battery);
	UFUNCTION()
	void ReactToBatterySlotStateChange(class ABatterySlot* Battery);
	
	UPROPERTY(BlueprintReadOnly)
	TArray<class ABatterySlot*> BatterySlots;

	UPROPERTY(BlueprintReadOnly)
	TArray<class ABatteryOnGround*> Batteries;
	
	UPROPERTY(BlueprintAssignable)
	FHackingCallback OnHackingFinished;

	UPROPERTY(BlueprintAssignable)
	FHackingAmmountCallback OnHackingStatusChange;

	virtual void Tick(float DeltaSeconds) override;
};
