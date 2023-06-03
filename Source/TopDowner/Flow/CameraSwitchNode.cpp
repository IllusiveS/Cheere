// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraSwitchNode.h"

#include "FlowComponent.h"
#include "FlowSubsystem.h"
#include "Kismet/GameplayStatics.h"

void UCameraSwitchNode::ExecuteInput(const FName& PinName)
{
	if (const UFlowSubsystem* FlowSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UFlowSubsystem>())
	{
		auto Components = FlowSubsystem->GetComponents<UFlowComponent>(CameraIdentityTags, MatchType, true).Array();

		UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetViewTargetWithBlend(Components[0]->GetOwner(), BlendTime, BlendFunc, BlendExp);

		FTimerHandle handle;
		GetWorld()->GetTimerManager().SetTimer(handle, this, &UCameraSwitchNode::FinishTimer, BlendTime, false);
	}
}

void UCameraSwitchNode::FinishTimer()
{
	TriggerFirstOutput(true);
}
#if WITH_EDITOR
FString UCameraSwitchNode::GetNodeDescription() const
{
	return GetIdentityTagsDescription(CameraIdentityTags);
}

EDataValidationResult UCameraSwitchNode::ValidateNode()
{
	if (CameraIdentityTags.IsEmpty())
	{
		ValidationLog.Error<UFlowNode>(TEXT("No camera tag set"), this);
		return EDataValidationResult::Invalid;
	}

	return EDataValidationResult::Valid;
}
#endif