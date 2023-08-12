// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "CombatSystemDeveloperSettings.generated.h"

class UBehaviorTree;

/**
 * 
 */
UCLASS(Config=Game, defaultconfig, meta = (DisplayName="Combat System Settings"))
class TOPDOWNER_API UCombatSystemDeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()
	
public:
	/* Default slot name if UI doesn't specify any */ 
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "General")
	FString SaveSlotName;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "General")
	TSoftObjectPtr<UBehaviorTree> CombatTree;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "General")
	int DesiredBasicEnemyAmount;
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "General")
	int DesiredSpecialEnemyAmount;
};
