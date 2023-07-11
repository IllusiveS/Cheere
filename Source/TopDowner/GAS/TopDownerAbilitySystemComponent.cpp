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

int UTopDownerAbilitySystemComponent::RunEvent(FGameplayTag EventTag, const FGameplayEventData Payload)
{
	return HandleGameplayEvent(EventTag, &Payload);
}

bool UTopDownerAbilitySystemComponent::HasTag(FGameplayTag TagToCheck)
{
	unimplemented();
	return false;
}

TArray<FGameplayAbilitySpecHandle> UTopDownerAbilitySystemComponent::RunGameplayAbilityFromEvent(FGameplayTag EventTag,
	const FGameplayEventData Payload)
{
	TArray<FGameplayAbilitySpecHandle> HandlesToReturn;
	int32 TriggeredCount = 0;
	FGameplayTag CurrentTag = EventTag;
	ABILITYLIST_SCOPE_LOCK();
	while (CurrentTag.IsValid())
	{
		if (GameplayEventTriggeredAbilities.Contains(CurrentTag))
		{
			TArray<FGameplayAbilitySpecHandle> TriggeredAbilityHandles = GameplayEventTriggeredAbilities[CurrentTag];

			for (const FGameplayAbilitySpecHandle& AbilityHandle : TriggeredAbilityHandles)
			{
				if (TriggerAbilityFromGameplayEvent(AbilityHandle, AbilityActorInfo.Get(), EventTag, &Payload, *this))
				{
					TriggeredCount++;
					HandlesToReturn.Add(AbilityHandle);
				}
			}
		}

		CurrentTag = CurrentTag.RequestDirectParent();
	}

	if (FGameplayEventMulticastDelegate* Delegate = GenericGameplayEventCallbacks.Find(EventTag))
	{
		// Make a copy before broadcasting to prevent memory stomping
		FGameplayEventMulticastDelegate DelegateCopy = *Delegate;
		DelegateCopy.Broadcast(&Payload);
	}

	// Make a copy in case it changes due to callbacks
	TArray<TPair<FGameplayTagContainer, FGameplayEventTagMulticastDelegate>> LocalGameplayEventTagContainerDelegates = GameplayEventTagContainerDelegates;
	for (TPair<FGameplayTagContainer, FGameplayEventTagMulticastDelegate>& SearchPair : LocalGameplayEventTagContainerDelegates)
	{
		if (SearchPair.Key.IsEmpty() || EventTag.MatchesAny(SearchPair.Key))
		{
			SearchPair.Value.Broadcast(EventTag, &Payload);
		}
	}

	return HandlesToReturn;
}

void UTopDownerAbilitySystemComponent::GetDamagedTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	unimplemented();
}
