// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/FlowNode.h"
#include "PlayAudioNode.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNER_API UPlayAudioNode : public UFlowNode
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	USoundBase* AudioToPlay;

	virtual void ExecuteInput(const FName& PinName) override;
};
