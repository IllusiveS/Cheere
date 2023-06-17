// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatController.h"

#include "TopDowner/EnemyRobot.h"

void ACombatController::BeginCombat()
{
	
}

void ACombatController::EndCombat()
{
	
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
