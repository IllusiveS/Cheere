// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatController.h"

#include "Algo/Accumulate.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "TopDowner/EnemyRobot.h"
#include "TopDowner/AI/EnemyGroup.h"

void ACombatController::BeginCombat()
{
}

void ACombatController::EndCombat()
{
	
}

void ACombatController::AddGroupToCombat(AEnemyGroup* NewGroup)
{
	GroupsInCombat.Add(NewGroup);
}

void ACombatController::RemoveGroupFromCombat(AEnemyGroup* GroupToRemove)
{
	GroupsInCombat.Remove(GroupToRemove);
}

AEnemyGroup* ACombatController::GetUnactivatedGroup()
{
	AEnemyGroup* GroupToReturn = nullptr;

	GroupsInCombat.Sort([](auto& Enemy1, auto& Enemy2)
	{
		return Enemy1.CostOfUnits > Enemy2.CostOfUnits;
	});
	
	for(const auto group : GroupsInCombat)
	{
		if (group == nullptr) continue;
		if (group->IsActivated == false && group->IsBeingMerged == false)
		{
			GroupToReturn = group;
			break;
		}
	}
	return GroupToReturn;
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
	NotActiveEnemiesInCombat.Add(NewRobot);
	AddEnemyToAmountMap(NewRobot);	
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
		bb->SetValueAsInt("ActiveGroups", Algo::Accumulate(GroupsInCombat, 0, [](auto val, auto Group){ return val + Group->IsActivated ? 1 : 0; }));
	}
}

void ACombatController::AddEnemyToAmountMap(AEnemyRobot* NewRobot)
{
	if (EnemiesAmounts.Contains(NewRobot->GetClass()))
	{
		EnemiesAmounts[NewRobot->GetClass()]++;
	} else
	{
		EnemiesAmounts[NewRobot->GetClass()] = 1;
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
