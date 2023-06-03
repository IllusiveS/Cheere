// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/FlowNode.h"
#include "CameraSwitchNode.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNER_API UCameraSwitchNode : public UFlowNode
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	FGameplayTagContainer CameraIdentityTags;
	
	UPROPERTY(EditAnywhere)
	float BlendTime;

	UPROPERTY(EditAnywhere)
	TEnumAsByte<EViewTargetBlendFunction> BlendFunc;

	UPROPERTY(EditAnywhere)
	float BlendExp{0};
	
	UPROPERTY(EditAnywhere)
	EGameplayContainerMatchType MatchType {EGameplayContainerMatchType::All};

protected:
	virtual void ExecuteInput(const FName& PinName) override;
	void FinishTimer();

#if WITH_EDITOR
public:
	virtual FString GetNodeDescription() const override;
	virtual EDataValidationResult ValidateNode() override;
#endif
};
