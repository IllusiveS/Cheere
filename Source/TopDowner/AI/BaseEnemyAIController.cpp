// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemyAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "EnvironmentQuery/EnvQuery.h"
#include "TopDowner/EnemyRobot.h"

void ABaseEnemyAIController::Tick(float DeltaSeconds)
{
	Super::Super::Tick(DeltaSeconds);
	
	UpdateControlRotation(DeltaSeconds, false);

	GetBlackboardComponent()->SetValueAsBool("IsActive", Cast<AEnemyRobot>(GetPawn())->IsActivated());

	if( auto Enemy = Cast<AEnemyRobot>(GetPawn()))
	{
		if(auto GetEnvQuery = Enemy->DefaultPositionTargetQuery)
		{
			GetBlackboardComponent()->SetValueAsObject("PositionEqs", GetEnvQuery);
		}
		
	}
}
