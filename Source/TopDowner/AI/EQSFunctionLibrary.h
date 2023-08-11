// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "EQSFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNER_API UEQSFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	UFUNCTION(BlueprintCallable, Category = "AI|EQS", meta = (WorldContext = "WorldContextObject"))
	static void StopEQSQueryByQuerier(UObject* WorldContextObject, UObject* Querier);
};
