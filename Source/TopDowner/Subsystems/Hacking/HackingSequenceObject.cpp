// Fill out your copyright notice in the Description page of Project Settings.


#include "HackingSequenceObject.h"

#include "FlowSubsystem.h"
#include "ObjectivesSubsystem.h"
#include "GameplayThings/BatteryOnGround.h"
#include "GameplayThings/BatterySlot.h"

AHackingSequenceObject::AHackingSequenceObject()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bTickEvenWhenPaused = true;
	PrimaryActorTick.TickGroup = TG_PrePhysics;
}

void AHackingSequenceObject::AddBatteryPower(float PowerToAdd)
{
	
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
					Actor->OnStateChange.AddDynamic(this, &AHackingSequenceObject::ReactToBatterySlotStateChange);
					ReactToBatterySlotStateChange(Actor);
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
					Actor->OnStateChange.AddDynamic(this, &AHackingSequenceObject::ReactToBatteryStateChange);
					ReactToBatteryStateChange(Actor);
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

void AHackingSequenceObject::ReactToBatteryStateChange(ABatteryOnGround* Battery)
{
	if (const auto Objectives = GetWorld()->GetGameInstance()->GetSubsystem<UObjectivesSubsystem>())
	{
		if (Battery->IsBeingUsed)
		{
			Objectives->MakeObjectiveUnactive(Battery);
		}
		else
		{
			Objectives->MakeObjectiveActive(Battery);
		}
	}
}

void AHackingSequenceObject::ReactToBatterySlotStateChange(ABatterySlot* BatterySlot)
{
	if (BatterySlot->IsActive)
	{
		ActiveBatterySlots.Emplace(BatterySlot);
	}
	else
	{
		ActiveBatterySlots.Remove(BatterySlot);
	}
	
	if (const auto Objectives = GetWorld()->GetGameInstance()->GetSubsystem<UObjectivesSubsystem>())
	{
		if (BatterySlot->IsActive)
		{
			Objectives->MakeObjectiveUnactive(BatterySlot);
		} else
		{
			Objectives->MakeObjectiveActive(BatterySlot);
		}
	}
}

void AHackingSequenceObject::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	float ValueToAdd = 0;
	for(auto Slot : ActiveBatterySlots)
	{
		ValueToAdd += 1 * DeltaSeconds;
	}

	CurrentPoints += BaseGain * DeltaSeconds;
	
	CurrentPoints += ValueToAdd;
	OnHackingStatusChange.Broadcast(CurrentPoints, PointsRequired);
	if (CurrentPoints >= PointsRequired)
	{
		EndHacking();
	}
}
