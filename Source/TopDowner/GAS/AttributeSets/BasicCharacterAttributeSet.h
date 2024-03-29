// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "BasicCharacterAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName) \

/**
 * 
 */
UCLASS()
class TOPDOWNER_API UBasicCharacterAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UBasicCharacterAttributeSet, MaxHealth)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	FGameplayAttributeData CurrentHealth;
	ATTRIBUTE_ACCESSORS(UBasicCharacterAttributeSet, CurrentHealth)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	FGameplayAttributeData DamageReceived;
	ATTRIBUTE_ACCESSORS(UBasicCharacterAttributeSet, DamageReceived)
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	FGameplayAttributeData HealingReceived;
	ATTRIBUTE_ACCESSORS(UBasicCharacterAttributeSet, HealingReceived)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	FGameplayAttributeData FireCooldown;
	ATTRIBUTE_ACCESSORS(UBasicCharacterAttributeSet, FireCooldown)
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	FGameplayAttributeData DamageDealt;
	ATTRIBUTE_ACCESSORS(UBasicCharacterAttributeSet, DamageDealt)
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	FGameplayAttributeData DeltaAmmo;
	ATTRIBUTE_ACCESSORS(UBasicCharacterAttributeSet, DeltaAmmo)
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	FGameplayAttributeData MaxAmmo;
	ATTRIBUTE_ACCESSORS(UBasicCharacterAttributeSet, MaxAmmo)
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	FGameplayAttributeData CurrentAmmo;
	ATTRIBUTE_ACCESSORS(UBasicCharacterAttributeSet, CurrentAmmo)
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	FGameplayAttributeData DeltaAPAmmo;
	ATTRIBUTE_ACCESSORS(UBasicCharacterAttributeSet, DeltaAPAmmo)
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	FGameplayAttributeData MaxAmmoAP;
	ATTRIBUTE_ACCESSORS(UBasicCharacterAttributeSet, MaxAmmoAP)
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	FGameplayAttributeData CurrentAmmoAP;
	ATTRIBUTE_ACCESSORS(UBasicCharacterAttributeSet, CurrentAmmoAP)
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	FGameplayAttributeData DeltaPushbackAmmo;
	ATTRIBUTE_ACCESSORS(UBasicCharacterAttributeSet, DeltaPushbackAmmo)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	FGameplayAttributeData MaxAmmoPushback;
	ATTRIBUTE_ACCESSORS(UBasicCharacterAttributeSet, MaxAmmoPushback)
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	FGameplayAttributeData CurrentAmmoPushback;
	ATTRIBUTE_ACCESSORS(UBasicCharacterAttributeSet, CurrentAmmoPushback)
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	FGameplayAttributeData Speed;
	ATTRIBUTE_ACCESSORS(UBasicCharacterAttributeSet, Speed)

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	UPROPERTY(EditAnywhere)
	float PushbackMultiplier {200.0f};
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Attributes")
	TSubclassOf<class UTopDownerGameplayEffect> DeadGameplayEffect;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Attributes")
	TSubclassOf<class UTopDownerGameplayEffect> DamageReceivedGameplayEffect;

	UFUNCTION(BlueprintPure)
	float GetNormalizedAmmo() const;

};
