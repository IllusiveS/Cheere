// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameplayEffectFuncLibrary.generated.h"

/**
 * 
 */
UCLASS()
class UGameplayEffectFuncLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable)
	static void SetSourceObject(FGameplayEffectContextHandle EffectContext, UObject* NewSourceObject);
};
