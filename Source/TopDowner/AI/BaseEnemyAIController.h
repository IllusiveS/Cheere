// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BaseEnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNER_API ABaseEnemyAIController : public AAIController
{
	GENERATED_BODY()

	virtual void Tick(float DeltaSeconds) override;
};
