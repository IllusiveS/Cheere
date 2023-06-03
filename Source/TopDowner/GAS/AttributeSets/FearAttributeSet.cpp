// Fill out your copyright notice in the Description page of Project Settings.


#include "FearAttributeSet.h"

#include "GameplayEffectExtension.h"
#include "TopDowner/GAS/TopDownerAbilitySystemComponent.h"
#include "TopDowner/GAS/TopDownerGameplayEffect.h"

void UFearAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetFearReceivedAttribute())
	{
		const float FearGained = GetFearReceived() * GetFearReceivedMultiplier();
		SetFearReceived(0.0);

		auto Component = Cast<UTopDownerAbilitySystemComponent>(GetOwningAbilitySystemComponent());
		
		if (FearGained > 0.0)
		{
			Component->AddEffect(Component, FearRecentlyGainedGameplayEffect);
		}
		
		const float NewFear = FearGained + GetCurrentFear();
		SetCurrentFear(FMath::Clamp(NewFear, 0.0, GetMaxFear()));

		if (GetCurrentFear() == GetMaxFear())
		{
			Component->AddEffect(Component, FearGameplayEffect);
		}
	}
}
