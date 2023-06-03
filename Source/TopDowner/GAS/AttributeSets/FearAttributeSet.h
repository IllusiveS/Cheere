// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "FearAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName) \

/**
 * 
 */
UCLASS()
class TOPDOWNER_API UFearAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FearAttributes")
	FGameplayAttributeData MaxFear;
	ATTRIBUTE_ACCESSORS(UFearAttributeSet, MaxFear)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FearAttributes")
	FGameplayAttributeData CurrentFear;
	ATTRIBUTE_ACCESSORS(UFearAttributeSet, CurrentFear)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FearAttributes")
	FGameplayAttributeData FearDecayDelay;
	ATTRIBUTE_ACCESSORS(UFearAttributeSet, FearDecayDelay)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FearAttributes")
	FGameplayAttributeData FearReceived;
	ATTRIBUTE_ACCESSORS(UFearAttributeSet, FearReceived)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FearAttributes")
	FGameplayAttributeData FearReceivedMultiplier;
	ATTRIBUTE_ACCESSORS(UFearAttributeSet, FearReceivedMultiplier)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FearAttributes")
	FGameplayAttributeData FearDecay;
	ATTRIBUTE_ACCESSORS(UFearAttributeSet, FearDecay)

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetFearNormalized() const { return CurrentFear.GetCurrentValue() / MaxFear.GetCurrentValue(); };

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FearAttributes")
	TSubclassOf<class UTopDownerGameplayEffect> FearGameplayEffect;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FearAttributes")
	TSubclassOf<class UTopDownerGameplayEffect> FearRecentlyGainedGameplayEffect;
};
