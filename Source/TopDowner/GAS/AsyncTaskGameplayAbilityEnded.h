// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "AsyncTaskGameplayAbilityEnded.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAsyncTaskGameplayAbilityEndedEv);

/**
 * 
 */
UCLASS(BlueprintType, meta = (ExposedAsyncProxy = AsyncTask))
class TOPDOWNER_API UAsyncTaskGameplayAbilityEnded : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FAsyncTaskGameplayAbilityEndedEv OnEnded;

	UPROPERTY(BlueprintAssignable)
	FAsyncTaskGameplayAbilityEndedEv OnEndedFail;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	static UAsyncTaskGameplayAbilityEnded* ListenForGameplayAbilityEnd(UAbilitySystemComponent* abilitySystemComponent, TSubclassOf<UGameplayAbility> abilityClass);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	static UAsyncTaskGameplayAbilityEnded* ListenForGameplayAbilityEndFromHandle(UAbilitySystemComponent* abilitySystemComponent, FGameplayAbilitySpecHandle handle);
	
	// You must call this function manually when you want the AsyncTask to end.
	// For UMG Widgets, you would call it in the Widget's Destruct event.
	UFUNCTION(BlueprintCallable)
	void EndTask();

protected:

	UPROPERTY()
	class UTopDownerGameplayAbility* AbilityListeningTo;
	
	UPROPERTY()
	UAbilitySystemComponent* ASC;
	FGameplayTagContainer TagsStillApplied;
	TMap<FGameplayTag, FDelegateHandle> HandlesMap;

	UFUNCTION()
	virtual void OnCallback(bool bWasCancelled);
};
