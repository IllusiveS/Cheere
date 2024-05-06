// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicCharacterAttributeSet.h"

#include "GameplayEffectExtension.h"
#include "GameFramework/Character.h"
#include "Logging/StructuredLog.h"
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
		const float CurrentHealthVal = GetCurrentHealth();
		const float NewHealth = CurrentHealthVal - LocalDamageDone;
		//CurrentHealth.SetCurrentValue(FMath::Clamp(NewHealth, 0.0f, GetMaxHealth()));
		SetCurrentHealth(FMath::Clamp(NewHealth, 0.0f, GetMaxHealth()));

		UE_LOGFMT(LogTemp, Log, "Before health: {0} Current health: {1} after receiving {2} damage", CurrentHealthVal, GetCurrentHealth(), LocalDamageDone);
		
		auto component = Cast<UTopDownerAbilitySystemComponent>(GetOwningAbilitySystemComponent());
		
		const FGameplayTag DamageTag = FGameplayTag::RequestGameplayTag(FName("Event.Damage"));
		FGameplayEventData EventData{};
		EventData.EventTag = DamageTag;
		EventData.EventMagnitude = LocalDamageDone;
		EventData.Target = GetOwningActor();
		EventData.Instigator = Data.EffectSpec.GetContext().GetInstigator();

		FGameplayTagContainer DamageTags;
		Data.EffectSpec.GetAllAssetTags(DamageTags);
		EventData.InstigatorTags = DamageTags;
		
		component->RunEvent(DamageTag, EventData);
		
		if (GetCurrentHealth() <= 0.0)
		{
			component->AddEffect(this, DeadGameplayEffect);
			// if (DeadGameplayEffect != nullptr && DeadGameplayEffect->IsValidLowLevel())
			// {
			// 	//Apply pushback
   //              if (auto SourceActor = Cast<ACharacter>(Data.EffectSpec.GetContext().GetInstigator()))
   //              {
   //              	auto CurrentActor = Cast<ACharacter>(Data.Target.GetOwnerActor());
   //  
   //              	const auto Origin = Data.EffectSpec.GetContext().GetOrigin();
   //              	const auto Dir = CurrentActor->GetActorLocation() - Origin;
   //              	const auto DirNormalized = Dir.GetSafeNormal();
   //              	
   //              	CurrentActor->GetMesh()->SetSimulatePhysics(true);
   //              	const auto RandomPushbackVector = FVector(FMath::FRandRange(-500.0, 500.0), FMath::FRandRange(-50.0, 50.0), FMath::FRandRange(-50.0, 50.0));
   //              	CurrentActor->GetMesh()->AddImpulse(DirNormalized * LocalDamageDone * PushbackMultiplier * FMath::RandRange(1.0, 1.9), NAME_None, true);
   //              }
			// }
		}
		if (DamageReceivedGameplayEffect != nullptr && DamageReceivedGameplayEffect->IsValidLowLevel())
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

	if (Data.EvaluatedData.Attribute == GetDeltaAmmoAttribute())
    {
    	// Store a local copy of the amount of damage done and clear the damage attribute
    	const float LocalAmmoDelta = GetDeltaAmmo();
    	SetDeltaAmmo(0.f);

    	// Apply the health change and then clamp it
    	const float NewAmmo = GetCurrentAmmo() + LocalAmmoDelta;
		const float MaxAmmoValue = GetMaxAmmo();
    	SetCurrentAmmo(FMath::Clamp(NewAmmo, 0.0f, MaxAmmoValue));
    }
	if (Data.EvaluatedData.Attribute == GetDeltaAPAmmoAttribute())
	{
		// Store a local copy of the amount of damage done and clear the damage attribute
		const float LocalAmmoDelta = GetDeltaAPAmmo();
		SetDeltaAPAmmo(0.f);

		// Apply the health change and then clamp it
		const float NewAmmo = GetCurrentAmmoAP() + LocalAmmoDelta;
		const float MaxAmmoValue = GetMaxAmmoAP();
		SetCurrentAmmoAP(FMath::Clamp(NewAmmo, 0.0f, MaxAmmoValue));
	}
	if (Data.EvaluatedData.Attribute == GetDeltaPushbackAmmoAttribute())
	{
		// Store a local copy of the amount of damage done and clear the damage attribute
		const float LocalAmmoDelta = GetDeltaAmmo();
		SetDeltaAmmo(0.f);

		// Apply the health change and then clamp it
		const float NewAmmo = GetCurrentAmmoPushback() + LocalAmmoDelta;
		const float MaxAmmoValue = GetMaxAmmoPushback();
		SetCurrentAmmoPushback(FMath::Clamp(NewAmmo, 0.0f, MaxAmmoValue));
	}
}

float UBasicCharacterAttributeSet::GetNormalizedAmmo() const
{
	return GetCurrentAmmo() / GetMaxAmmo();
}
