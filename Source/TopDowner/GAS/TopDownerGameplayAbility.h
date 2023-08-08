// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "TopDownerGameplayAbility.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGameplayAbilityEnded, bool, WasCancelled);

/**
 * 
 */
UCLASS()
class TOPDOWNER_API UTopDownerGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
public:
	UTopDownerGameplayAbility();
	
	UPROPERTY(BlueprintAssignable)
	FGameplayAbilityEnded OnAbilityEnded;
	
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
};
