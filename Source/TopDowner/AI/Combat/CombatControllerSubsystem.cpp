// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatControllerSubsystem.h"


#include "CombatController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "CombatSystemDeveloperSettings.h"
#include "BehaviorTree/BlackboardComponent.h"

UCombatControllerSubsystem::UCombatControllerSubsystem()
{
}

void UCombatControllerSubsystem::StartCombat(TMap<TSubclassOf<AEnemyRobot>, int> DesiredEnemies)
{
	if(CombatController == nullptr)
	{
		CombatController = GetWorld()->SpawnActor<ACombatController>(ACombatController::StaticClass(), FVector{0.0f}, FRotator{0.0});
	}
	CombatController->RunBehaviorTree(CombatTree);

	const UCombatSystemDeveloperSettings* SGSettings = GetDefault<UCombatSystemDeveloperSettings>();
	
	auto BB = CombatController->GetBlackboardComponent();
	CombatController->GetBlackboardComponent()->SetValueAsInt("DesiredSpecialEnemiesActive", SGSettings->DesiredSpecialEnemyAmount);
	CombatController->GetBlackboardComponent()->SetValueAsInt("DesiredBasicEnemiesActive", SGSettings->DesiredBasicEnemyAmount);
	CombatController->GetBlackboardComponent()->SetValueAsInt("DesiredNumberOfMeleeActive", SGSettings->DesiredMeleeEnemyAmount);
	CombatController->DesiredEnemies = DesiredEnemies;
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

	auto World = WorldContextObject->GetWorld();
	auto GameInstance = World->GetGameInstance();
	auto Subsystem = GameInstance->GetSubsystem<UCombatControllerSubsystem>();
	if (Subsystem)
	{
		if (Subsystem->CombatController == nullptr)[[unlikely]]
		{
			Subsystem->CombatController = World->SpawnActor<ACombatController>(ACombatController::StaticClass(), FVector{0.0f}, FRotator{0.0});
		}
		return Subsystem->CombatController;
	}
	return nullptr;
}
