// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FlowAsset.h"
#include "TestFlowSubgraph.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class TOPDOWNER_API UTestFlowSubgraph : public UFlowAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	float TestValue;
};
