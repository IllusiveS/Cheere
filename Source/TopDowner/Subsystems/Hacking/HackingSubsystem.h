// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HackingSequenceObject.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "HackingSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHackingObjectChange, UHackingSequenceObject*, Object);

/**
 * 
 */
UCLASS()
class TOPDOWNER_API UHackingSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UHackingSequenceObject> CurrentCombat;

	UFUNCTION(BlueprintCallable)
	void PrepareHacking();
	
	UFUNCTION(BlueprintCallable)
	void BeginHacking();

	UFUNCTION(BlueprintCallable)
	void FinishHacking();

	UPROPERTY(BlueprintAssignable)
	FOnHackingObjectChange OnHackingBegin;

	UPROPERTY(BlueprintAssignable)
	FOnHackingObjectChange OnHackingEnd;
};
