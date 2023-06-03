// Fill out your copyright notice in the Description page of Project Settings.


#include "DodgeAttributeSet.h"

#include "AbilitySystemInterface.h"
#include "GameplayEffectExtension.h"
#include "TopDowner/GAS/TopDownerGameplayEffect.h"

void UDodgeAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetCurrentDodgeChargeGainAttribute())
	{
		const auto Gain = GetCurrentDodgeChargeGain();
		SetCurrentDodgeChargeGain(0.0);

		if (GetCurrentDodgeAmount() == GetMaxDodgeAmount())
		{
			SetCurrentDodgeCharge(0.0);
			return;
		}
		SetCurrentDodgeCharge(Gain + GetCurrentDodgeCharge());
		if (GetCurrentDodgeCharge() >= 1.0)
		{
			if (GetCurrentDodgeAmount() < GetMaxDodgeAmount())
			{
				const IAbilitySystemInterface* ASI = Cast<IAbilitySystemInterface>(Data.EffectSpec.GetContext().GetInstigator());
				auto Context = ASI->GetAbilitySystemComponent()->MakeEffectContext();
				Context.AddInstigator(Data.Target.GetOwnerActor(), Data.Target.GetOwnerActor());
				TObjectPtr<UTopDownerGameplayEffect> effect = GainDodgeEffect.GetDefaultObject();
				ASI->GetAbilitySystemComponent()->ApplyGameplayEffectToTarget(effect, &Data.Target, 1.0, Context);
				SetCurrentDodgeCharge(0.0);
			} else
			{
				SetCurrentDodgeCharge(1.0);
			}
		}
	}
}
