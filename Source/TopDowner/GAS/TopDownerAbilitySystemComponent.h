// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "TopDownerGameplayEffect.h"
#include "TopDownerAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNER_API UTopDownerAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

	friend struct FActiveGameplayEffect;
	friend struct FActiveGameplayEffectAction;
	friend struct FActiveGameplayEffectsContainer;
	friend struct FActiveGameplayCue;
	friend struct FActiveGameplayCueContainer;
	friend struct FGameplayAbilitySpec;
	friend struct FGameplayAbilitySpecContainer;
	friend struct FAggregator;
	friend struct FActiveGameplayEffectAction_Add;
	friend struct FGameplayEffectSpec;
	friend class UGameplayAbility;
	friend class AAbilitySystemDebugHUD;
	friend class UAbilitySystemGlobals;
	
public:
	virtual void BeginPlay() override;
	void InitCallbacks();
	
	UFUNCTION(BlueprintCallable, Category = "Effects")
	void InitEffects();
	
	UFUNCTION(BlueprintCallable, Category = "Effects")
	bool AddEffect(UObject* Giver, TSubclassOf<UTopDownerGameplayEffect> effect);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Effects")
	TArray<TSubclassOf<class UTopDownerGameplayEffect>> DefaultEffects;

	UFUNCTION(BlueprintCallable)
	int RunEvent(FGameplayTag EventTag, const FGameplayEventData Payload);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool HasTag(FGameplayTag TagToCheck);

	UFUNCTION(BlueprintCallable)
	TArray<FGameplayAbilitySpecHandle> RunGameplayAbilityFromEvent(FGameplayTag EventTag, const FGameplayEventData Payload);
	
	bool CanActivateAnyAbility(FGameplayTag Tag, FGameplayEventData Payload);

	// UFUNCTION()
	// int GetNumberOfAvailableAbilitiesByTag(FGameplayTag EventTag, const FGameplayEventData Payload) const;
	
	//ReactionToChange	
	virtual void GetDamagedTagChanged(const FGameplayTag CallbackTag, int32 NewCount);
};
