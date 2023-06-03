// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BackpackItem.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNER_API UBackpackItem : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	int Amount;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UTopDownerGameplayEffect> EffectToApplyWhenEquipped;

	UPROPERTY(EditAnywhere)
	UTexture2D* ItemTexture;
};
