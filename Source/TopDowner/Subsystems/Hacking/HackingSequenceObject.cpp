// Fill out your copyright notice in the Description page of Project Settings.


#include "HackingSequenceObject.h"

#include "FlowSubsystem.h"
#include "GameplayThings/BatteryOnGround.h"
#include "GameplayThings/BatterySlot.h"

void AHackingSequenceObject::AddBatteryPower(float PowerToAdd)
{
	CurrentPoints += PowerToAdd;
	OnHackingStatusChange.Broadcast(CurrentPoints, PointsRequired);
	if (CurrentPoints >= PointsRequired)
	{
		EndHacking();
	}
}

void AHackingSequenceObject::GatherBatterySlots(FGameplayTagContainer IdentityTags)
{
	if (const UFlowSubsystem* FlowSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UFlowSubsystem>())
	{
		auto BatterySlotsFlows = FlowSubsystem->GetComponents<UFlowComponent>(IdentityTags, EGameplayContainerMatchType::All, true).Array();

		if (!BatterySlotsFlows.IsEmpty())
		{
			for (auto Slot : BatterySlotsFlows)
			{
				if (Slot.IsValid() == false) continue;
				if (ABatterySlot* Actor = Cast<ABatterySlot>(Slot.Get()->GetOuter())) {
					BatterySlots.Add(Actor);
				}
			}
		}
	}
}

void AHackingSequenceObject::GatherBatteries(FGameplayTagContainer IdentityTags)
{
	if (const UFlowSubsystem* FlowSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UFlowSubsystem>())
	{
		auto BatterySlotsFlows = FlowSubsystem->GetComponents<UFlowComponent>(IdentityTags, EGameplayContainerMatchType::All, true).Array();

		if (!BatterySlotsFlows.IsEmpty())
		{
			for (auto Slot : BatterySlotsFlows)
			{
				if (Slot.IsValid() == false) continue;
				if (auto Actor = Cast<ABatteryOnGround>(Slot.Get()->GetOuter())) {
					Batteries.Add(Actor);
				}
			}
		}
	}
}

void AHackingSequenceObject::BeginHacking()
{
	
}

ABatteryOnGround* AHackingSequenceObject::GetBatteryToSteal()
{
	for (auto Battery : Batteries)
	{
		if (Battery->IsBeingUsed)
		{
			return Battery;
		}
	}
	return nullptr;
}

void AHackingSequenceObject::EndHacking()
{
	OnHackingFinished.Broadcast();
}
