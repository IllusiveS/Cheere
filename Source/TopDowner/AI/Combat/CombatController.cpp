// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatController.h"

#include "BrainComponent.h"
#include "Algo/Accumulate.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "TopDowner/EnemyRobot.h"
#include "TopDowner/TopDowner.h"
#include "TopDowner/AI/EnemyGroup.h"

void ACombatController::BeginCombat()
{
	//GetBrainComponent()->StartLogic();
}

void ACombatController::EndCombat()
{
	GetBrainComponent()->StopLogic("Combat End");
}

void ACombatController::AddGroupToCombat(AEnemyGroup* NewGroup)
{
	GroupsInCombat.Add(NewGroup);
	BoredGroups.Add(NewGroup);
}

void ACombatController::RemoveGroupFromCombat(AEnemyGroup* GroupToRemove)
{
	GroupsInCombat.Remove(GroupToRemove);
	BoredGroups.Remove(GroupToRemove);
}

AEnemyGroup* ACombatController::GetUnactivatedGroup()
{
	AEnemyGroup* GroupToReturn = nullptr;
	
	GroupsInCombat.Sort([](auto& Enemy1, auto& Enemy2)
	{
		return Enemy1.CostOfUnits > Enemy2.CostOfUnits;
	});

	GroupsInCombat = GroupsInCombat.FilterByPredicate([](auto& Group) { return Group->IsValidLowLevel();});

	UE_LOG(LogTopDowner, Log, TEXT("Finding group among %i"), GroupsInCombat.Num());
	for(const auto group : GroupsInCombat)
	{
		if (group == nullptr)
		{
			UE_LOG(LogTopDowner, Log, TEXT("Group corrupted"));
			continue;
		}
		UE_LOG(LogTopDowner, Log, TEXT("Processing group %s"), *group->GetName());
		if (group->IsActivated == false && group->IsValidLowLevel())
		{
			UE_LOG(LogTopDowner, Log, TEXT("Found correct group"));
			GroupToReturn = group;
			break;
		}
	}
	//UE_LOG(LogTopDowner, Log, TEXT("Returned group %s"), GroupToReturn ? *GroupToReturn->GetName() : TEXT("NULL"));
	return GroupToReturn;
}

AEnemyGroup* ACombatController::GetBoredGroup()
{
	AEnemyGroup* GroupToReturn = nullptr;

	BoredGroups = BoredGroups.FilterByPredicate([](auto Group){ return Group != nullptr && !Group->IsActivated;});
	if (BoredGroups.IsEmpty()) return nullptr;
	
	const auto RandomIndex = FMath::RandRange(0, BoredGroups.Num() - 1);

	auto Group = BoredGroups[RandomIndex];

	FTimerHandle TimerHandle_AttackDelay;
	FTimerDelegate Delegate; // Delegate to bind function with parameters
	Delegate.BindUFunction(this, "TimerOnBoredomEnded", Group);

	GetWorld()->GetTimerManager().SetTimer(TimerHandle_AttackDelay, Delegate, FMath::FRandRange(3.0, 6.0), false);
	
	return Group;
}

void ACombatController::TimerOnBoredomEnded(AEnemyGroup* Group)
{
	BoredGroups.Add(Group);
}

AEnemyGroup* ACombatController::FindNearestAcceptableGroup(AEnemyRobot* Enemy)
{
	AEnemyGroup* GroupToReturn = nullptr;

	for(auto Group : GroupsInCombat)
	{
		if (Group == nullptr) continue;
		if (Group->CanJoinGroup(Enemy))
		{
			return Group;
		}
	}
	GroupsInCombat.RemoveAll([](auto Group) { return Group == nullptr;});
	
	return GroupToReturn;
}

void ACombatController::AddEnemyToCombat(AEnemyRobot* NewRobot)
{
	AllEnemiesInCombat.Add(NewRobot);
	EnemyActivations.Add(NewRobot, EActivationType::None);
	AddEnemyToAmountMap(NewRobot);

	NewRobot->OnEnemyDead.AddDynamic(this, &ACombatController::ReactToEnemyDied);
	NewRobot->OnEnemyActivated.AddDynamic(this, &ACombatController::ReactToEnemyActivationChange);
}

void ACombatController::AddRequiredEnemyToCombat(AEnemyRobot* NewRobot)
{
	AllEnemiesInCombatRequired.Add(NewRobot);
	AddEnemyToCombat(NewRobot);
}

void ACombatController::RemoveEnemyFromCombat(AEnemyRobot* NewRobot)
{
	AllEnemiesInCombatRequired.Remove(NewRobot);
	AllEnemiesInCombat.Remove(NewRobot);

	RemoveEnemyRobotFromAmountMap(NewRobot);
}

void ACombatController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (const auto bb = GetBlackboardComponent())
	{
		GroupsInCombat = GroupsInCombat.FilterByPredicate([](auto Group) { return Group != nullptr; });

		bb->SetValueAsInt("SpecialEnemiesActive", GetNumberOfActiveSpecialEnemies());
		bb->SetValueAsInt("BasicEnemiesActive", GetNumberOfActiveBasicEnemies());
		bb->SetValueAsInt("NumberOfMeleeActive", GetNumberOfActiveMeleeEnemies());
	}
}

AEnemyRobot* ACombatController::GetRandomUnactiveEnemy(EEnemyType EnemyType) const
{
	AEnemyRobot* EnemyToReturn = nullptr;

	TSet<AEnemyRobot*> PossibleOptions;
	for(const auto Enemy : AllEnemiesInCombat)
	{
		if (Enemy->ActivationType == EActivationType::None && Enemy->EnemyType == EnemyType)
		{
			PossibleOptions.Add(Enemy);
		}
	}
	
	if (PossibleOptions.IsEmpty()) return nullptr;

	EnemyToReturn = PossibleOptions.Array()[FMath::RandRange(0, PossibleOptions.Num() - 1)];
	return EnemyToReturn;
}

AEnemyRobot* ACombatController::GetRandomUnactiveBasicEnemy() const
{
	AEnemyRobot* EnemyToReturn = nullptr;

	TSet<AEnemyRobot*> PossibleOptions;
	for(const auto Enemy : AllEnemiesInCombat)
	{
		if (Enemy->ActivationType == EActivationType::None && Enemy->EnemyType == EEnemyType::Basic)
		{
			PossibleOptions.Add(Enemy);
		}
	}
	
	if (PossibleOptions.IsEmpty()) return nullptr;

	EnemyToReturn = PossibleOptions.Array()[FMath::RandRange(0, PossibleOptions.Num() - 1)];
	return EnemyToReturn;
}

int ACombatController::GetNumberOfBasicEnemies() const
{
	const int ReturnValue = Algo::Accumulate(AllEnemiesInCombat, 0, [](int Result, auto const Enemy)
	{
		Result += Enemy->EnemyType == EEnemyType::Basic ? 1 : 0;
		return Result;
	});
	return ReturnValue;
}

int ACombatController::GetNumberOfActiveBasicEnemies() const
{
	const int ReturnValue = Algo::Accumulate(AllEnemiesInCombat, 0, [](int Result, auto const Enemy)
	{
		Result += Enemy->IsActivated() && Enemy->EnemyType == EEnemyType::Basic ? 1 : 0;
		return Result;
	});
	return ReturnValue;
}

int ACombatController::GetNumberOfActiveMeleeEnemies() const
{
	const int ReturnValue = Algo::Accumulate(AllEnemiesInCombat, 0, [](int Result, auto const Enemy)
	{
		Result += Enemy->IsActivated() && Enemy->EnemyType == EEnemyType::Melee ? 1 : 0;
		return Result;
	});
	return ReturnValue;
}

AEnemyRobot* ACombatController::GetRandomUnactiveSpecialEnemy() const
{
	AEnemyRobot* EnemyToReturn = nullptr;

	TSet<AEnemyRobot*> PossibleOptions;
	for(const auto Enemy : AllEnemiesInCombat)
	{
		if (Enemy->ActivationType == EActivationType::None && Enemy->EnemyType == EEnemyType::Special)
		{
			PossibleOptions.Add(Enemy);
		}
	}
	
	if (PossibleOptions.IsEmpty()) return nullptr;

	EnemyToReturn = PossibleOptions.Array()[FMath::RandRange(0, PossibleOptions.Num())];
	return EnemyToReturn;
}

int ACombatController::GetNumberOfSpecialEnemies()
{
	const int ReturnValue = Algo::Accumulate(AllEnemiesInCombat, 0, [](int Result, auto const Enemy)
	{
		Result += Enemy->EnemyType == EEnemyType::Special ? 1 : 0;
		return Result;
	});
	return ReturnValue;
}

int ACombatController::GetNumberOfActiveSpecialEnemies()
{
	const int ReturnValue = Algo::Accumulate(AllEnemiesInCombat, 0, [](int Result, auto const Enemy)
	{
		Result += Enemy->IsActivated() && Enemy->EnemyType == EEnemyType::Special ? 1 : 0;
		return Result;
	});
	return ReturnValue;
}
void ACombatController::ReactToEnemyActivationChange(AEnemyRobot* Enemy, EActivationType Activation)
{
	EnemyActivations[Enemy] = Activation;
}

void ACombatController::ReactToEnemyActivatedLow(AEnemyRobot* Enemy)
{
	ReactToEnemyActivationChange(Enemy, EActivationType::Low);
}

void ACombatController::ReactToEnemyActivatedHigh(AEnemyRobot* Enemy)
{
	ReactToEnemyActivationChange(Enemy, EActivationType::High);
}

void ACombatController::ReactToEnemyDeactivated(AEnemyRobot* Enemy)
{
	ReactToEnemyActivationChange(Enemy, EActivationType::None);
}

void ACombatController::ReactToEnemyDied(AEnemyRobot* Enemy)
{
	AllEnemiesInCombat.Remove(Enemy);
	EnemyActivations.Remove(Enemy);
	RemoveEnemyRobotFromAmountMap(Enemy);

	Enemy->OnEnemyDead.RemoveDynamic(this, &ACombatController::ReactToEnemyDied);
	Enemy->OnEnemyActivated.RemoveDynamic(this, &ACombatController::ReactToEnemyActivationChange);
}

int ACombatController::GetNumOfUnits(TSubclassOf<AEnemyRobot> ClassToTest) const
{
	if(EnemiesAmounts.Contains(ClassToTest))
	{
		return EnemiesAmounts[ClassToTest];
	}
	return 0;
}

int ACombatController::GetDesiredNumOfUnits(TSubclassOf<AEnemyRobot> ClassToTest) const
{
	if(DesiredEnemies.Contains(ClassToTest))
	{
		return DesiredEnemies[ClassToTest];
	}
	return 0;
}

int ACombatController::GetNumOfEnemiesByActivation(EActivationType Activation) const
{
	TArray<EActivationType> Activations;
	int FoundAmmount = 0;
	EnemyActivations.GenerateValueArray(Activations);
	for (auto Act : Activations)
	{
			if (Act == Activation) FoundAmmount++;
	}
	return FoundAmmount;
}

void ACombatController::AddEnemyToAmountMap(AEnemyRobot* NewRobot)
{
	if (EnemiesAmounts.Contains(NewRobot->GetClass()))
	{
		EnemiesAmounts[NewRobot->GetClass()]++;
	} else
	{
		EnemiesAmounts.Add(NewRobot->GetClass(), 1);
	}
}

void ACombatController::RemoveEnemyRobotFromAmountMap(AEnemyRobot* NewRobot)
{
	if (EnemiesAmounts.Contains(NewRobot->GetClass()))
	{
		EnemiesAmounts[NewRobot->GetClass()]--;
		if (EnemiesAmounts[NewRobot->GetClass()] == 0) EnemiesAmounts.Remove(NewRobot->GetClass());
	}
}
