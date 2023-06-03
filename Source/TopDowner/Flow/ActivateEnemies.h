// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/FlowNode.h"
#include "ActivateEnemies.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNER_API UActivateEnemies : public UFlowNode
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	FGameplayTagContainer IdentityTags;
	
	UPROPERTY(EditAnywhere)
	FGameplayTagContainer ActivationTag;

	UPROPERTY()
	FGameplayTag EnemyTag {FGameplayTag::RequestGameplayTag("Entity.Type.Enemy")};
	
	UPROPERTY()
	FGameplayTag NotifyTag {FGameplayTag::RequestGameplayTag("NotifyTags.SpawnController")};

	UPROPERTY(EditAnywhere)
	EGameplayContainerMatchType MatchType {EGameplayContainerMatchType::All};

	UPROPERTY(EditAnywhere, Category = "Notify")
	EFlowNetMode NetMode;

	virtual void ExecuteInput(const FName& PinName) override;
};
