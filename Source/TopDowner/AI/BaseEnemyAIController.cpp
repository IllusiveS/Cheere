// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemyAIController.h"

void ABaseEnemyAIController::Tick(float DeltaSeconds)
{
	Super::Super::Tick(DeltaSeconds);
	
	UpdateControlRotation(DeltaSeconds, false);
}
