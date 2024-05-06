// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "TimeDilationSlowdownSubsystem.generated.h"


UENUM(BlueprintType)
enum class ESlowdownType
{
	E_Cutscene
	,E_Death
	,E_Hit
	,E_Other
};
/**
 * 
 */
UCLASS()
class TOPDOWNER_API UTimeDilationSlowdownSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void SetAimingSlowTime(float DilationAmount);
	
	UFUNCTION(BlueprintCallable)
	void SlowTime(float DilationAmount, float DilationTime, bool ForceNew = false, TEnumAsByte<ESlowdownType> SlowdownType = ESlowdownType::E_Other);

	UFUNCTION()
	void OnSlowTimeEnded();
private:
	ESlowdownType CurrentSlowdown;
	FTimerHandle CurrentSlowdownHandle;
	float CurrentSlowdownAmount;
	float CurrentAimingSlowdown {1.0f};
};
