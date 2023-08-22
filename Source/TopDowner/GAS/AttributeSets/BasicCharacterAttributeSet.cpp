// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicCharacterAttributeSet.h"

#include "GameplayEffectExtension.h"
#include "GameFramework/Character.h"
#include "TopDowner/GAS/TopDownerAbilitySystemComponent.h"

void UBasicCharacterAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetDamageReceivedAttribute())
	{
		// Store a local copy of the amount of damage done and clear the damage attribute
		const float LocalDamageDone = GetDamageReceived();
		SetDamageReceived(0.f);

		// Apply the health change and then clamp it
		const float NewHealth = GetCurrentHealth() - LocalDamageDone;
		SetCurrentHealth(FMath::Clamp(NewHealth, 0.0f, GetMaxHealth()));
	
		auto component = Cast<UTopDownerAbilitySystemComponent>(GetOwningAbilitySystemComponent());
		
		if (GetCurrentHealth() <= 0.0)
		{
			component->AddEffect(this, DeadGameplayEffect);
			if (DeadGameplayEffect != nullptr && DeadGameplayEffect->IsValidLowLevel())
			{
				//Apply pushback
                if (auto SourceActor = Cast<ACharacter>(Data.EffectSpec.GetContext().GetInstigator()))
                {
                	auto CurrentActor = Cast<ACharacter>(Data.Target.GetOwnerActor());
    
                	const auto Origin = Data.EffectSpec.GetContext().GetOrigin();
                	const auto Dir = CurrentActor->GetActorLocation() - Origin;
                	const auto DirNormalized = Dir.GetSafeNormal();
                	
                	CurrentActor->GetMesh()->SetSimulatePhysics(true);
                	CurrentActor->GetMesh()->AddImpulse(DirNormalized * LocalDamageDone * PushbackMultiplier * FMath::RandRange(1.0, 1.9), NAME_None, true);
                }
			}
		}
		component->AddEffect(this, DamageReceivedGameplayEffect);
	}

	if (Data.EvaluatedData.Attribute == GetHealingReceivedAttribute())
	{
		// Store a local copy of the amount of damage done and clear the damage attribute
		const float LocalHealingDone = GetHealingReceived();
		SetHealingReceived(0.f);

		// Apply the health change and then clamp it
		const float NewHealth = GetCurrentHealth() + LocalHealingDone;
		SetCurrentHealth(FMath::Clamp(NewHealth, 0.0f, GetMaxHealth()));
	}
}
