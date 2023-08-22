// Fill out your copyright notice in the Description page of Project Settings.


#include "AsyncTaskGameplayAbilityEnded.h"

#include "AbilitySystemComponent.h"
#include "TopDownerGameplayAbility.h"

UAsyncTaskGameplayAbilityEnded* UAsyncTaskGameplayAbilityEnded::ListenForGameplayAbilityEnd(
	UAbilitySystemComponent* abilitySystemComponent, TSubclassOf<UGameplayAbility> abilityClass)
{
	if (!IsValid(abilitySystemComponent))
	{
		//Print::Say("Couldn't create Task, missing ASC");
		return nullptr;
	}

	auto abilitySpec = abilitySystemComponent->FindAbilitySpecFromClass(abilityClass);
	if (abilitySpec == nullptr)
	{
		//Print::Say("Couldn't create Task, Ability " + abilityClass->GetName() + " not found in ASC");
		return nullptr;
	}
	
	auto abilityInstance = abilitySpec->GetPrimaryInstance();
	if (abilityInstance == nullptr)
	{
		//Print::Say("Couldn't create Task, Ability " + abilityClass->GetName() + " couldn't find an instance. Instance Policy shouldn't be 'instance per execution'");
		return nullptr;
	}
	
	UTopDownerGameplayAbility* abilityCrow = Cast<UTopDownerGameplayAbility>(abilityInstance);
	if (abilityCrow == nullptr)
	{
		//Print::Say("Couldn't create Task, Ability " + abilityClass->GetName() + " needs to inherit from UGameplayAbility_Crow");
		return nullptr;
	}

	UAsyncTaskGameplayAbilityEnded* r = NewObject<UAsyncTaskGameplayAbilityEnded>();
	abilityCrow->OnAbilityEnded.AddDynamic(r, &UAsyncTaskGameplayAbilityEnded::OnCallback);
	r->AbilityListeningTo = abilityCrow;

	return r;
}

UAsyncTaskGameplayAbilityEnded* UAsyncTaskGameplayAbilityEnded::ListenForGameplayAbilityEndFromHandle(
	UAbilitySystemComponent* abilitySystemComponent, FGameplayAbilitySpecHandle handle)
{
	if (!IsValid(abilitySystemComponent))
	{
		//Print::Say("Couldn't create Task, missing ASC");
		return nullptr;
	}

	auto abilitySpec = abilitySystemComponent->FindAbilitySpecFromHandle(handle);
	if (abilitySpec == nullptr)
	{
		//Print::Say("Couldn't create Task, Ability " + abilityClass->GetName() + " not found in ASC");
		return nullptr;
	}
	
	auto abilityInstance = abilitySpec->GetPrimaryInstance();
	if (abilityInstance == nullptr)
	{
		//Print::Say("Couldn't create Task, Ability " + abilityClass->GetName() + " couldn't find an instance. Instance Policy shouldn't be 'instance per execution'");
		return nullptr;
	}
	
	UTopDownerGameplayAbility* abilityCrow = Cast<UTopDownerGameplayAbility>(abilityInstance);
	if (abilityCrow == nullptr)
	{
		//Print::Say("Couldn't create Task, Ability " + abilityClass->GetName() + " needs to inherit from UGameplayAbility_Crow");
		return nullptr;
	}

	UAsyncTaskGameplayAbilityEnded* r = NewObject<UAsyncTaskGameplayAbilityEnded>();
	abilityCrow->OnAbilityEnded.AddDynamic(r, &UAsyncTaskGameplayAbilityEnded::OnCallback);
	r->AbilityListeningTo = abilityCrow;

	return r;
}

void UAsyncTaskGameplayAbilityEnded::EndTask()
{
	if (IsValid(AbilityListeningTo))
	{
		AbilityListeningTo->OnAbilityEnded.RemoveDynamic(this, &UAsyncTaskGameplayAbilityEnded::OnCallback);
	}
	
	SetReadyToDestroy();
	MarkAsGarbage();
}

void UAsyncTaskGameplayAbilityEnded::OnCallback(bool bWasCancelled)
{
	if (bWasCancelled)
	{
		OnEndedFail.Broadcast();
	} else
	{
		OnEnded.Broadcast();
	}
	AbilityListeningTo->OnAbilityEnded.RemoveDynamic(this, &UAsyncTaskGameplayAbilityEnded::OnCallback);
}
