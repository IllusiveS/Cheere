// Fill out your copyright notice in the Description page of Project Settings.


#include "BTD_CanActivateAbilityByTag.h"

#include "TopDowner/EnemyRobot.h"
#include "TopDowner/GAS/TopDownerAbilitySystemComponent.h"

bool UBTD_CanActivateAbilityByTag::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp,
                                                              uint8* NodeMemory) const
{
	const bool bSuccess = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);
	if (!bSuccess) return false;

	if (AEnemyRobot* AIPawn = Cast<AEnemyRobot>(OwnerComp.GetAIOwner()->GetPawn()))
	{
		auto GASComponent = AIPawn->AbilitySystemComponent;
		const bool result = GASComponent->HasActivatableTriggeredAbility(Tag);
		return result;
	}
	
	return false;
}
