// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "DodgeAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName) \

/**
 * 
 */
UCLASS()
class TOPDOWNER_API UDodgeAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	FGameplayAttributeData CurrentDodgeCharge;
	ATTRIBUTE_ACCESSORS(UDodgeAttributeSet, CurrentDodgeCharge)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	FGameplayAttributeData CurrentDodgeChargeGain;
	ATTRIBUTE_ACCESSORS(UDodgeAttributeSet, CurrentDodgeChargeGain)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	FGameplayAttributeData CurrentDodgeAmount;
	ATTRIBUTE_ACCESSORS(UDodgeAttributeSet, CurrentDodgeAmount)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	FGameplayAttributeData MaxDodgeAmount;
	ATTRIBUTE_ACCESSORS(UDodgeAttributeSet, MaxDodgeAmount)

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UTopDownerGameplayEffect> GainDodgeEffect;
};
