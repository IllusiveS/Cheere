// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatControllerSubsystem.h"


#include "CombatController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "CombatSystemDeveloperSettings.h"
#include "BehaviorTree/BlackboardComponent.h"

UCombatControllerSubsystem::UCombatControllerSubsystem()
{
}

void UCombatControllerSubsystem::StartCombat()
{
	CombatController->RunBehaviorTree(CombatTree);
	
	auto BB = CombatController->GetBlackboardComponent();
	CombatController->GetBlackboardComponent()->SetValueAsInt("ActiveGroups", 0);
	CombatController->GetBlackboardComponent()->SetValueAsInt("DesiredActiveGroupsNumber", 3);
	CombatController->BeginCombat();
}

void UCombatControllerSubsystem::EndCombat()
{
	CombatController->GetBrainComponent()->StopLogic("Combat end");
}

void UCombatControllerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	CombatController = GetWorld()->SpawnActor<ACombatController>(ACombatController::StaticClass(), FVector{0.0f}, FRotator{0.0});
	
	const UCombatSystemDeveloperSettings* SGSettings = GetDefault<UCombatSystemDeveloperSettings>();
	
	CombatTree = SGSettings->CombatTree.LoadSynchronous();
}

ACombatController* UCombatControllerFunctionLibrary::GetCombatController(const UObject* WorldContextObject)
{
	if (WorldContextObject == nullptr) return nullptr;
	if (const auto Subsystem = WorldContextObject->GetWorld()->GetGameInstance()->GetSubsystem<UCombatControllerSubsystem>())
	{
		return Subsystem->CombatController;
	}
	return nullptr;
}
