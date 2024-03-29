// Fill out your copyright notice in the Description page of Project Settings.


#include "HackingSequence.h"

#include "ObjectivesSubsystem.h"
#include "TopDowner/Subsystems/Hacking/HackingSequenceObject.h"
#include "TopDowner/Subsystems/Hacking/HackingSubsystem.h"

const FString OutputAfterStart = "Output";
const FString OutputAfterHackingSuccess = "Finished";

UHackingSequence::UHackingSequence()
{
#if WITH_EDITOR
	Category = TEXT("Spawning");
	NodeStyle = EFlowNodeStyle::Latent;
#endif

	//OutputPins.Empty();
	//OutputPins.Add(FFlowPin(OutputAfterStart));
	OutputPins.Add(FFlowPin(OutputAfterHackingSuccess));
}

void UHackingSequence::ExecuteInput(const FName& PinName)
{
	if(UHackingSubsystem * HackingSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UHackingSubsystem>())
	{
		HackingSubsystem->PrepareHacking(GetWorld(), Data);

		if( AHackingSequenceObject* Obj = HackingSubsystem->CurrentCombat )
		{
			Obj->OnHackingFinished.AddDynamic(this, &UHackingSequence::UHackingSequence::OnHackingDone);
		}

		HackingSubsystem->BeginHacking();
	}
	
	TriggerFirstOutput(false);
	Super::ExecuteInput(PinName);
}

void UHackingSequence::OnHackingDone()
{
	if(UHackingSubsystem * HackingSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UHackingSubsystem>())
	{
		if( AHackingSequenceObject* Obj = HackingSubsystem->CurrentCombat )
		{
			Obj->OnHackingFinished.RemoveDynamic(this, &UHackingSequence::UHackingSequence::OnHackingDone);
		}
	}
	
	TriggerOutput(*OutputAfterHackingSuccess, true);
}
