// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "DevToolsDeveloperSettings.generated.h"

/**
 * 
 */
UCLASS(Config=Game, defaultconfig, meta = (DisplayName="Dev tools settings"))
class TOPDOWNER_API UDevToolsDeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()
    	
    public:
		//Gameplay effect to apply to give max possible ammo
    	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Effects")
    	TSoftClassPtr<class UTopDownerGameplayEffect> InfiniteAmmoEffectClass;
};
