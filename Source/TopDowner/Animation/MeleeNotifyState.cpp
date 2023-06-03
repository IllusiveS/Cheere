// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeNotifyState.h"

#include "MeleeAnimInterface.h"
#include "Kismet/KismetSystemLibrary.h"

void UMeleeNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration,
                                    const FAnimNotifyEventReference& EventReference)
{
    const auto Owner = MeshComp->GetOwner();
    if (Owner == nullptr) return;
    
	if(Owner->Implements<UMeleeAnimInterface>())
	{
		IMeleeAnimInterface::Execute_BeginAttack(MeshComp->GetOwner());
	}
	
}

void UMeleeNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime,
	const FAnimNotifyEventReference& EventReference)
{
	const auto Owner = MeshComp->GetOwner();
	if (Owner == nullptr) return;
	
	const auto StartVector = MeshComp->GetSocketLocation(SocketNameBegin);
	const auto EndVector = MeshComp->GetSocketLocation(SocketNameEnd);
	TArray<FHitResult> hits;
	
	UKismetSystemLibrary::SphereTraceMultiForObjects(
		MeshComp->GetWorld()
		, StartVector, EndVector
		, SphereSize
		, QueryType, false
		, TArray<AActor*>()
		, DrawDebugType
		, hits, true
		, FLinearColor::Red, FLinearColor::Green, 0.2);

	
	if(Owner->Implements<UMeleeAnimInterface>())
	{
		for (auto& result : hits)
		{
			IMeleeAnimInterface::Execute_ReceiveAttackInfo(MeshComp->GetOwner(), result);
		}
	}
}

void UMeleeNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	const auto Owner = MeshComp->GetOwner();
	if (Owner == nullptr) return;
	
	if(Owner->Implements<UMeleeAnimInterface>())
	{
		IMeleeAnimInterface::Execute_EndAttack(MeshComp->GetOwner());
	}
}
