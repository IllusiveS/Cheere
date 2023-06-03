// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MeleeAnimInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UMeleeAnimInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TOPDOWNER_API IMeleeAnimInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, Category = Interact)
	void BeginAttack();
	UFUNCTION(BlueprintNativeEvent, Category = Interact)
	void EndAttack();
	UFUNCTION(BlueprintNativeEvent, Category = Interact)
	void ReceiveAttackInfo(FHitResult result);
};
