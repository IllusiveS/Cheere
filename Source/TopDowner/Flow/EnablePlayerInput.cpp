// Fill out your copyright notice in the Description page of Project Settings.


#include "EnablePlayerInput.h"

#include "Kismet/GameplayStatics.h"

void UEnablePlayerInput::ExecuteInput(const FName& PinName)
{
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->EnableInput(nullptr);
	
	TriggerFirstOutput(true);
}
