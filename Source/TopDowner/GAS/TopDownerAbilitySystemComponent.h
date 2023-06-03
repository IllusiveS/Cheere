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
public:
	virtual void BeginPlay() override;
	void InitCallbacks();
	
	UFUNCTION(BlueprintCallable, Category = "Effects")
	void InitEffects();
	
	UFUNCTION(BlueprintCallable, Category = "Effects")
	void AddEffect(UObject* Giver, TSubclassOf<UTopDownerGameplayEffect> effect);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Effects")
	TArray<TSubclassOf<class UTopDownerGameplayEffect>> DefaultEffects;

	UFUNCTION(BlueprintCallable)
	void RunEvent(FGameplayTag EventTag, const FGameplayEventData Payload);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool HasTag(FGameplayTag TagToCheck);
	
	//ReactionToChange	
	virtual void GetDamagedTagChanged(const FGameplayTag CallbackTag, int32 NewCount);
};
