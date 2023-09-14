// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputTriggers.h"
#include "AlwaysActive.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNER_API UAlwaysActive : public UInputTrigger
{
	GENERATED_BODY()
public:
	
	virtual ETriggerState UpdateState_Implementation(const UEnhancedPlayerInput* PlayerInput, FInputActionValue ModifiedValue, float DeltaTime) override;
};
