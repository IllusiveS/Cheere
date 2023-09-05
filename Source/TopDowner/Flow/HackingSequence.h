// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/FlowNode.h"
#include "TopDowner/Subsystems/Hacking/HackingSubsystem.h"
#include "HackingSequence.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNER_API UHackingSequence : public UFlowNode
{
	GENERATED_BODY()

public:
	UHackingSequence();

	UPROPERTY(EditAnywhere)
	FHackingStartStructData Data;

	virtual void ExecuteInput(const FName& PinName) override;

	UFUNCTION()
	void OnHackingDone();
};
