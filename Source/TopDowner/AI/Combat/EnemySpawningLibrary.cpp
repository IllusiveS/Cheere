// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawningLibrary.h"

#include "FlowSubsystem.h"
#include "Algo/Accumulate.h"
#include "TopDowner/EnemyRobot.h"
#include "TopDowner/Flow/SpawnEnemiesNode.h"

void UEnemySpawningLibrary::SpawnEnemy(UObject* WorldContextObject, FEnemySpawnData SpawnData)
{
	auto World = WorldContextObject->GetWorld();
	if (const UFlowSubsystem* FlowSubsystem = WorldContextObject->GetWorld()->GetGameInstance()->GetSubsystem<UFlowSubsystem>())
	{
		auto Components = FlowSubsystem->GetComponents<UFlowComponent>(SpawnData.SpawnerIdentityTags, SpawnData.MatchType, true).Array();

		if (!Components.IsEmpty())
		{
			auto WholeSpawnNumber = 0;

			auto FinishSpawnFunction = [SpawnData, World](UFlowComponent* target, TSubclassOf<AActor> EnemySpawner, TSubclassOf<class AEnemyRobot> EnemyToSpawn)
			{
				auto Spawner = target->GetOwner()->GetWorld()->SpawnActor(EnemySpawner
								,&target->GetOwner()->GetTransform());

				if(SpawnData.EffectToGive != nullptr && SpawnData.EffectToGive->IsValidLowLevel())
				{
					IEnemySpawnerInterface::Execute_SetUniqueEffect(Spawner, SpawnData.EffectToGive);
				}

				if(SpawnData.FlowTagsToGive.IsEmpty() == false)
				{
					IEnemySpawnerInterface::Execute_SetUniqueFlowTag(Spawner, SpawnData.FlowTagsToGive);
				}
				IEnemySpawnerInterface::Execute_SetEnemyToSpawn(Spawner, EnemyToSpawn);

				auto Enemy = IEnemySpawnerInterface::Execute_GetSpawnedEnemy(Spawner);
				if (SpawnData.ShouldAutoActivate)
				{
					FTimerHandle TimerHandle;
					FTimerDelegate Delegate;
					Delegate.BindUFunction(Enemy, "SpawnDefaultController");
					World->GetWorld()->GetTimerManager().SetTimer(TimerHandle, Delegate, 0.5, false);
				}
				
			};

			auto NumberOfEnemies = Algo::Accumulate(SpawnData.EnemiesToSpawn, 0, [](auto Acc, auto&& pair)
			{
				return pair.Value + Acc;
			});
	
			if (NumberOfEnemies <= Components.Num())
			{
				for (const TPair<TSubclassOf<class AEnemyRobot>, int> &pair : SpawnData.EnemiesToSpawn)
				{
					for (int i = 0; i < pair.Value; i++)
					{
						WholeSpawnNumber += 1;
						const auto RandIndex = FMath::RandRange(0, Components.Num() - 1);
						auto target = Components[RandIndex];

						FActorSpawnParameters params;

						//FGameplayTag TagRequest = FGameplayTag::RequestGameplayTag(TEXT("Level.Train.1Platform"));
						//ensure(target->IdentityTags.HasTag(TagRequest));
						
						if (SpawnData.DelayBetweenSpawns != 0.0)
						{
							FTimerHandle handle;
							target->GetOwner()->GetWorld()->GetTimerManager().SetTimer(handle, [=]()
							{
								FinishSpawnFunction(target.Get(), SpawnData.EnemySpawner, pair.Key);
							}, (WholeSpawnNumber + 1) * SpawnData.DelayBetweenSpawns, false);
						} else
						{
							FinishSpawnFunction(target.Get(), SpawnData.EnemySpawner, pair.Key);
						}
			
						Components.RemoveAt(RandIndex);
					}
				}
			} else
			{
			}
		} else
		{
		}
	}
}
