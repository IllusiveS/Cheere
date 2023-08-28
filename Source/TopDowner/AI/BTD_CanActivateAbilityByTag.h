// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTD_CanActivateAbilityByTag.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNER_API UBTD_CanActivateAbilityByTag : public UBTDecorator
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	FGameplayTag Tag;

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
