// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayAudioNode.h"

#include "Kismet/GameplayStatics.h"

void UPlayAudioNode::ExecuteInput(const FName& PinName)
{
	Super::ExecuteInput(PinName);

	UGameplayStatics::PlaySound2D(GetWorld(), AudioToPlay);

	TriggerFirstOutput(true);
}
