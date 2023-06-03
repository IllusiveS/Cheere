// Fill out your copyright notice in the Description page of Project Settings.


#include "TopDownerAbilitySystemComponent.h"

void UTopDownerAbilitySystemComponent::BeginPlay()
{
	Super::BeginPlay();
	InitCallbacks();
}

void UTopDownerAbilitySystemComponent::InitCallbacks()
{
	InitEffects();
}

void UTopDownerAbilitySystemComponent::InitEffects()
{
	for (const TSubclassOf<UTopDownerGameplayEffect> Effect : DefaultEffects)
    {
    	AddEffect(this, Effect);
    }
}

void UTopDownerAbilitySystemComponent::AddEffect(UObject* Giver, TSubclassOf<UTopDownerGameplayEffect> Effect)
{
	TSubclassOf<UTopDownerGameplayEffect>& EffectRef = Effect;

	FGameplayEffectContextHandle EffectContext = MakeEffectContext();
	EffectContext.AddSourceObject(Giver);

	FGameplayEffectSpecHandle EffectSpecHandle = MakeOutgoingSpec(Effect, 1, EffectContext);

	if(EffectSpecHandle.IsValid())
	{
		TObjectPtr<UTopDownerGameplayEffect> effect = EffectRef.GetDefaultObject();
		FActiveGameplayEffectHandle EffectHandle = ApplyGameplayEffectToSelf(effect, 1, EffectContext);
	}
}

void UTopDownerAbilitySystemComponent::RunEvent(FGameplayTag EventTag, const FGameplayEventData Payload)
{
	HandleGameplayEvent(EventTag, &Payload);
}

bool UTopDownerAbilitySystemComponent::HasTag(FGameplayTag TagToCheck)
{
	unimplemented();
	return false;
}

void UTopDownerAbilitySystemComponent::GetDamagedTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	unimplemented();
}
