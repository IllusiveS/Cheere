// Fill out your copyright notice in the Description page of Project Settings.


#include "ActivateEnemies.h"

#include "FlowComponent.h"
#include "FlowSubsystem.h"
#include "TopDowner/AI/Combat/CombatControllerSubsystem.h"

void UActivateEnemies::ExecuteInput(const FName& PinName)
{
	if (const UFlowSubsystem* FlowSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UFlowSubsystem>())
	{
		auto TagToSearch = IdentityTags;
		TagToSearch.AddTag(EnemyTag);

		auto Notify = ActivationTag;
		Notify.AddTag(NotifyTag);
		
		for (const TWeakObjectPtr<UFlowComponent>& Component : FlowSubsystem->GetComponents<UFlowComponent>(TagToSearch, MatchType, true))
		{
			Component->NotifyFromGraph(Notify, NetMode);
		}
	}
	if (UCombatControllerSubsystem* CombatSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UCombatControllerSubsystem>())
	{
		//CombatSubsystem->StartCombat();
	}
	
	TriggerFirstOutput(true);
}
