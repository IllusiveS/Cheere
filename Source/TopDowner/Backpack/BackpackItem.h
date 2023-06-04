// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "UObject/NoExportTypes.h"
#include "BackpackItem.generated.h"

UCLASS(BlueprintType)
class UBackpackItemAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	int MaxAmount;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<class UTopDownerGameplayEffect> EffectToApplyWhenEquipped;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UTexture2D* ItemUITexture;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UStaticMesh* ItemMesh;
};

USTRUCT(BlueprintType)
struct FItemUIRepresentation
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly)
	UBackpackItemAsset* ItemAsset;

	UPROPERTY(BlueprintReadOnly)
	int Amount;
};

/**
 * 
 */
UCLASS(BlueprintType)
class TOPDOWNER_API UBackpackItem : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	int Amount;

	UPROPERTY(BlueprintReadOnly)
	UBackpackItemAsset* ItemAsset;

	UFUNCTION(BlueprintPure)
	FItemUIRepresentation GetUIStruct() const;
};
