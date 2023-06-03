// Fill out your copyright notice in the Description page of Project Settings.


#include "DisablePlayerInput.h"

#include "InputActionValue.h"
#include "Kismet/GameplayStatics.h"
#include "TopDowner/TopDownerCharacter.h"

void UDisablePlayerInput::ExecuteInput(const FName& PinName)
{
	auto Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	Controller->DisableInput(nullptr);

	auto Player = Cast<ATopDownerCharacter>(Controller->GetPawn());
	FInputActionValue lel;
	Player->EndAim(lel);
	
	TriggerFirstOutput(true);
}
