// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnEnemiesNode.h"

#include "FlowComponent.h"
#include "FlowSubsystem.h"
#include "Algo/Accumulate.h"
#include "TopDowner/EnemyRobot.h"
#include "TopDowner/TopDowner.h"

USpawnEnemiesNode::USpawnEnemiesNode()
{
#if WITH_EDITOR
	Category = TEXT("Spawning");
	NodeStyle = EFlowNodeStyle::Latent;
#endif

	OutputPins.Empty();
	OutputPins.Add(FFlowPin(TEXT("StartedSpawn")));
	OutputPins.Add(FFlowPin(TEXT("FinishedSpawn")));
	OutputPins.Add(FFlowPin(TEXT("EnemiesDead")));
	
	static ConstructorHelpers::FObjectFinder<UClass> Spawner (TEXT("/Script/Engine.Blueprint'/Game/TopDown/LevelElements/BP_EnemySpawnerAnimation.BP_EnemySpawnerAnimation_C'"));
	EnemySpawner = Spawner.Object;
}

void USpawnEnemiesNode::RemoveEnemyFromSpawned(AEnemyRobot* Robot)
{
	SpawnedEnemies.Remove(Robot);

	if (SpawnedEnemies.IsEmpty())
	{
		TriggerOutput(TEXT("EnemiesDead"), true);
	}
}

void USpawnEnemiesNode::ExecuteInput(const FName& PinName)
{
	if (const UFlowSubsystem* FlowSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UFlowSubsystem>())
	{
		auto Components = FlowSubsystem->GetComponents<UFlowComponent>(SpawnerIdentityTags, MatchType, true).Array();

		if (!Components.IsEmpty())
		{
			auto WholeSpawnNumber = 0;

			auto FinishSpawnFunction = [this](UFlowComponent* target, TSubclassOf<AActor> EnemySpawner, TSubclassOf<class AEnemyRobot> EnemyToSpawn)
			{
				auto Spawner = target->GetOwner()->GetWorld()->SpawnActor(EnemySpawner
								,&target->GetOwner()->GetTransform());

				if(EffectToGive != nullptr && EffectToGive->IsValidLowLevel())
				{
					IEnemySpawnerInterface::Execute_SetUniqueEffect(Spawner, EffectToGive);
				}

				if(FlowTagsToGive.IsEmpty() == false)
				{
					IEnemySpawnerInterface::Execute_SetUniqueFlowTag(Spawner, FlowTagsToGive);
				}
				IEnemySpawnerInterface::Execute_SetEnemyToSpawn(Spawner, EnemyToSpawn);

				auto Enemy = IEnemySpawnerInterface::Execute_GetSpawnedEnemy(Spawner);
				if (Enemy)
				{
					SpawnedEnemies.Add(Enemy);
					Enemy->OnEnemyDead.AddDynamic(this, &USpawnEnemiesNode::RemoveEnemyFromSpawned);
				}
				
			};

			auto NumberOfEnemies = Algo::Accumulate(EnemiesToSpawn, 0, [](auto Acc, auto&& pair)
			{
				return pair.Value + Acc;
			});
	
			if (NumberOfEnemies <= Components.Num())
			{
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
			} else
			{
				UE_LOG(LogTopDowner, Log, TEXT("Not enough spawners found, spawn less enemies or put in more spawners."));
				FinishSpawning();
			}
		} else
		{
			UE_LOG(LogTopDowner, Log, TEXT("Did not found spawners with desired tag %s"), *SpawnerIdentityTags.ToString());
			FinishSpawning();
		}
	}

	TriggerFirstOutput(true);
}

void USpawnEnemiesNode::FinishSpawning()
{
	TriggerOutput(TEXT("FinishedSpawn"), false);
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