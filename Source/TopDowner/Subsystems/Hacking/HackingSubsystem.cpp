// Fill out your copyright notice in the Description page of Project Settings.


#include "HackingSubsystem.h"

#include "HackingSequenceObject.h"
#include "HackingSystemDeveloperSettings.h"
#include "ObjectivesSubsystem.h"
#include "ObjectiveWidget.h"
#include "GameplayThings/BatteryOnGround.h"

void UHackingSubsystem::PrepareHacking(UWorld* world, FHackingStartStructData Data)
{
	CurrentCombat = world->SpawnActor<AHackingSequenceObject>(AHackingSequenceObject::StaticClass());
	CurrentCombat->PointsRequired = Data.PointsRequired;
	CurrentCombat->GatherBatteries(Data.BatteryIdentityTags);
	CurrentCombat->GatherBatterySlots(Data.BatterySlotsIdentityTags);
	
	const auto HackingObjectiveSettings = GetDefault<UHackingSystemDeveloperSettings>();
	
	const auto ObjectiveWidget = HackingObjectiveSettings->ObjectiveWidget.LoadSynchronous();
	const auto BatteryObjectiveTexture = HackingObjectiveSettings->BatteryObjectiveTexture.LoadSynchronous();
	
	if(auto ObjectivesSubsystem = world->GetGameInstance()->GetSubsystem<UObjectivesSubsystem>())
	{
		ObjectivesSubsystem->PushLayer();

		for(const auto Battery : CurrentCombat->Batteries)
		{
			ObjectivesSubsystem->AddObjective(Battery, BatteryObjectiveTexture, ObjectiveWidget);
		}
	}
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
