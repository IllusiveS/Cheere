// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "MovementAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName) \

/**
 * 
 */
UCLASS()
class TOPDOWNER_API UMovementAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MovementAttributes")
	FGameplayAttributeData MaxWalkSpeed;
	ATTRIBUTE_ACCESSORS(UMovementAttributeSet, MaxWalkSpeed)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MovementAttributes")
	FGameplayAttributeData MaxAcceleration;
	ATTRIBUTE_ACCESSORS(UMovementAttributeSet, MaxAcceleration)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MovementAttributes")
	FGameplayAttributeData GroundFriction;
	ATTRIBUTE_ACCESSORS(UMovementAttributeSet, GroundFriction)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MovementAttributes")
	FGameplayAttributeData BrakingDecelerationWalking;
	ATTRIBUTE_ACCESSORS(UMovementAttributeSet, BrakingDecelerationWalking)
};
