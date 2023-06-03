// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnEnemiesNode.h"

#include "FlowComponent.h"
#include "FlowSubsystem.h"
#include "TopDowner/EnemyRobot.h"

USpawnEnemiesNode::USpawnEnemiesNode()
{
#if WITH_EDITOR
	Category = TEXT("Spawning");
	NodeStyle = EFlowNodeStyle::Latent;
#endif

	InputPins.Add(FFlowPin(TEXT("Start")));

	OutputPins.Empty();
	OutputPins.Add(FFlowPin(TEXT("StartedSpawn")));
	OutputPins.Add(FFlowPin(TEXT("FinishedSpawn")));
	
	static ConstructorHelpers::FObjectFinder<UClass> Spawner (TEXT("/Script/Engine.Blueprint'/Game/TopDown/LevelElements/BP_EnemySpawnerAnimation.BP_EnemySpawnerAnimation_C'"));
	EnemySpawner = Spawner.Object;
}

void USpawnEnemiesNode::ExecuteInput(const FName& PinName)
{
	if (const UFlowSubsystem* FlowSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UFlowSubsystem>())
	{
		auto Components = FlowSubsystem->GetComponents<UFlowComponent>(SpawnerIdentityTags, MatchType, true).Array();

		auto WholeSpawnNumber = 0;

		auto FinishSpawnFunction = [this](UFlowComponent* target, TSubclassOf<AActor> EnemySpawner, TSubclassOf<class AEnemyRobot> EnemyToSpawn)
		{
			
			auto Spawner = target->GetOwner()->GetWorld()->SpawnActor(EnemySpawner
							,&target->GetOwner()->GetTransform());

			if(EffectToGive->IsValidLowLevel())
			{
				IEnemySpawnerInterface::Execute_SetUniqueEffect(Spawner, EffectToGive);
			}

			if(FlowTagsToGive.IsEmpty() == false)
			{
				IEnemySpawnerInterface::Execute_SetUniqueFlowTag(Spawner, FlowTagsToGive);
			}
			IEnemySpawnerInterface::Execute_SetEnemyToSpawn(Spawner, EnemyToSpawn);
		};
		
		for (const TPair<TSubclassOf<class AEnemyRobot>, int> &pair : EnemiesToSpawn)
		{
			for (int i = 0; i < pair.Value; i++)
			{
				WholeSpawnNumber += 1;
				const auto RandIndex = FMath::RandRange(0, Components.Num() - 1);
				auto target = Components[RandIndex];

				FActorSpawnParameters params;

				if (DelayBetweenSpawns != 0.0)
				{
					FTimerHandle handle;
					target->GetOwner()->GetWorld()->GetTimerManager().SetTimer(handle, [=]()
					{
						FinishSpawnFunction(target.Get(), EnemySpawner, pair.Key);
					}, (WholeSpawnNumber + 1) * DelayBetweenSpawns, false);
				} else
				{
					FinishSpawnFunction(target.Get(), EnemySpawner, pair.Key);
				}
			
				Components.RemoveAt(RandIndex);
			}
		}

		if (DelayBetweenSpawns != 0.0)
		{
			FTimerHandle handle;
			GetWorld()->GetTimerManager().SetTimer(handle, this, &USpawnEnemiesNode::FinishSpawning, WholeSpawnNumber * DelayBetweenSpawns, false);
		}
	}

	TriggerFirstOutput(true);
}

void USpawnEnemiesNode::FinishSpawning()
{
	TriggerOutput(TEXT("FinishedSpawn"), true);
}

#if WITH_EDITOR
FString USpawnEnemiesNode::GetNodeDescription() const
{
	return GetIdentityTagsDescription(SpawnerIdentityTags);
}

EDataValidationResult USpawnEnemiesNode::ValidateNode()
{
	if (SpawnerIdentityTags.IsEmpty())
	{
		ValidationLog.Error<UFlowNode>(TEXT("No spawner tag set"), this);
		return EDataValidationResult::Invalid;
	}

	if (EnemiesToSpawn.IsEmpty())
	{
		ValidationLog.Error<UFlowNode>(TEXT("No enemy class set"), this);
		return EDataValidationResult::Invalid;
	}

	return EDataValidationResult::Valid;
}
#endif