// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyGroup.generated.h"

UCLASS(Blueprintable, BlueprintType)
class TOPDOWNER_API AEnemyGroup : public AActor
{
	GENERATED_BODY()
	
public:
	AEnemyGroup();
	
	/** Please add a function description */
	UFUNCTION(BlueprintCallable)
	void MergeAnotherGroup(AEnemyGroup* GroupToMergeIn);

	/** Please add a function description */
	UFUNCTION(BlueprintCallable)
	void UpdateUnitCosts();

	virtual void Tick(float DeltaSeconds) override;
public:
	/** Please add a variable description */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Default")
	TObjectPtr<class USphereComponent> Detection;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Default")
	TObjectPtr<class UStaticMeshComponent> StaticMesh;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Default")
	TObjectPtr<class USceneComponent> DefaultSceneRoot;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category="Default")
	TArray<class AEnemyRobot*> EnemiesInRange;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Default")
	int32 CostOfUnits {0};

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Default")
	int32 MaxCostOfUnits {4};

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Default")
	bool IsBeingMerged {false};

protected:
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent
		, AActor* OtherActor
		, UPrimitiveComponent* OtherComp
		, int32 OtherBodyIndex
		, bool bFromSweep
		, const FHitResult & SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent
		, AActor* OtherActor
		, UPrimitiveComponent* OtherComp
		, int32 OtherBodyIndex);
};
