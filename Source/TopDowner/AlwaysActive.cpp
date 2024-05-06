// Fill out your copyright notice in the Description page of Project Settings.


#include "AlwaysActive.h"

ETriggerState UAlwaysActive::UpdateState_Implementation(const UEnhancedPlayerInput* PlayerInput,
	FInputActionValue ModifiedValue, float DeltaTime)
{
	return ETriggerState::Triggered;
}
