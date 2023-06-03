// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "MeleeNotifyState.generated.h"

namespace EDrawDebugTrace
{
	enum Type : int;
}

/**
 * 
 */
UCLASS()
class TOPDOWNER_API UMeleeNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	// SocketName to attach to
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimNotify", meta = (AnimNotifyBoneName = "true"))
	FName SocketNameBegin;

	// SocketName to attach to
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimNotify", meta = (AnimNotifyBoneName = "true"))
	FName SocketNameEnd;

	UPROPERTY(EditAnywhere)
	TEnumAsByte<EDrawDebugTrace::Type> DrawDebugType;
	
	// SocketName to attach to
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimNotify")
	float SphereSize;

	UPROPERTY(EditAnywhere, Category = "AnimNotify")
	TArray<TEnumAsByte<EObjectTypeQuery>> QueryType;

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
