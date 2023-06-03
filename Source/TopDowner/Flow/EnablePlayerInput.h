// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/FlowNode.h"
#include "EnablePlayerInput.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNER_API UEnablePlayerInput : public UFlowNode
{
	GENERATED_BODY()
	
public:
	virtual void ExecuteInput(const FName& PinName) override;
};
