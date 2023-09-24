// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "GameplayEffectTypes.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GASHelpers.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNER_API UGASHelpers : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	static float GetSnapshotedValue(const FGameplayEffectSpecHandle &Spec, FGameplayAttribute Attribute);
};
