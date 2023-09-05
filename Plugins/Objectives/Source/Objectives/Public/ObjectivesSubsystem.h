// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ObjectivesSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class OBJECTIVES_API UObjectivesSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	UObjectivesMainWidget* Parent{nullptr};
	
	UPROPERTY()
	TMap<AActor*, class UObjectiveWidget*> ObjectiveWidgets;

	void Setup(AActor* Actor, TSubclassOf<UObjectivesMainWidget> MainClass);
	
	UFUNCTION(BlueprintCallable)
	void AddObjective(AActor* Actor, UTexture2D* Texture, TSubclassOf<UObjectiveWidget> ObjectiveWidget, TSubclassOf<UObjectivesMainWidget> MainClass);

	UFUNCTION(BlueprintCallable)
	void RemoveObjective(AActor* Actor);

	UFUNCTION(BlueprintCallable)
	void RemoveAllObjectives();
};
