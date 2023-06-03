// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "TimeDilationSlowdownSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNER_API UTimeDilationSlowdownSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void SlowTime(float DilationAmount, float DilationTime, bool ForceNew = false);

	UFUNCTION()
	void OnSlowTimeEnded();

	FTimerHandle CurrentSlowdownHandle;
	float CurrentSlowdownAmount;
};
