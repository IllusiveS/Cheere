// Fill out your copyright notice in the Description page of Project Settings.


#include "HackingSubsystem.h"

#include "HackingSequenceObject.h"

void UHackingSubsystem::PrepareHacking(UWorld* world, FHackingStartStructData Data)
{
	CurrentCombat = world->SpawnActor<AHackingSequenceObject>(AHackingSequenceObject::StaticClass());
	CurrentCombat->PointsRequired = Data.PointsRequired;
	CurrentCombat->GatherBatteries(Data.BatteryIdentityTags);
	CurrentCombat->GatherBatterySlots(Data.BatterySlotsIdentityTags);
}

void UHackingSubsystem::BeginHacking()
{
	CurrentCombat->BeginHacking();
	OnHackingBegin.Broadcast(CurrentCombat);
	CurrentCombat->OnHackingFinished.AddDynamic(this, &UHackingSubsystem::FinishHacking);
}

void UHackingSubsystem::FinishHacking()
{
	OnHackingEnd.Broadcast(CurrentCombat);
	CurrentCombat = nullptr;
}
