// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ObjectivesSubsystem.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogObjectives, Log, All);

USTRUCT(Blueprintable)
struct FObjectiveDataStruct
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly)
	class UObjectiveWidget* ObjectiveWidget;
	UPROPERTY(BlueprintReadOnly)
	AActor* TargetActor;
	UPROPERTY(BlueprintReadOnly)
	int Layer;
};

USTRUCT()
struct FObjectiveLayerDataStruct
{
	GENERATED_BODY()
public:
	TArray<FObjectiveDataStruct> Objectives;
};

/**
 * 
 */
UCLASS()
class OBJECTIVES_API UObjectivesSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	TArray<FObjectiveLayerDataStruct> ObjectiveWidgets {};

	int CurrentLayer = 0;

	int GetCurrentLayer() const;
	UFUNCTION()
	void SetLayer(int NewLayer);
	UFUNCTION(BlueprintCallable)
	void PushLayer();
	UFUNCTION(BlueprintCallable)
	void PopLayer();
	
	UFUNCTION(BlueprintCallable)
	void AddObjective(AActor* Actor, UTexture2D* Texture, TSubclassOf<UObjectiveWidget> ObjectiveWidget);

	UFUNCTION(BlueprintCallable)
	void RemoveObjective(AActor* Actor);

	void MakeObjectiveActive(AActor* Actor);
	void MakeObjectiveUnactive(AActor* Actor);

	void AddToWidgetsMap(const FObjectiveDataStruct &Data);
	
	UFUNCTION(BlueprintCallable)
	void RemoveAllObjectives();
};
