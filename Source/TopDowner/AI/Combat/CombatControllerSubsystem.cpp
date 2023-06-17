// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatControllerSubsystem.h"


#include "CombatController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "CombatSystemDeveloperSettings.h"

UCombatControllerSubsystem::UCombatControllerSubsystem()
{
	CombatController = CreateDefaultSubobject<ACombatController>(TEXT("Controller"));
}

void UCombatControllerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	const UCombatSystemDeveloperSettings* SGSettings = GetDefault<UCombatSystemDeveloperSettings>();
	
	CombatTree = SGSettings->CombatTree.GetDefaultObject();
}

ACombatController* UCombatControllerFunctionLibrary::GetCombatController(const UObject* WorldContextObject)
{
	if (const auto Subsystem = WorldContextObject->GetWorld()->GetGameInstance()->GetSubsystem<UCombatControllerSubsystem>())
	{
		return Subsystem->CombatController;
	}
	return nullptr;
}
