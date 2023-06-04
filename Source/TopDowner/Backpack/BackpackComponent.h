// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BackpackComponent.generated.h"

USTRUCT(BlueprintType)
struct FBackpackUIData
{
	GENERATED_BODY()
	TArray<FItemUIRepresentation> Items;
	int CurrentIndex;
	
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMoveBackpackUpDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMoveBackpackDownDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FBackpackUpdate, const TArray<FItemUIRepresentation>&, Items, int, CurrentItem, int, PrevIndex, int, NextIndex);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOPDOWNER_API UBackpackComponent : public UActorComponent
{
	GENERATED_BODY()


	
public:	
	// Sets default values for this component's properties
	UBackpackComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool CanPickupItem(class UBackpackItemAsset* ItemToPickUp) const;

	UFUNCTION(BlueprintCallable)
	void PickupItem(class UBackpackItemAsset* ItemToPickUp);

	UFUNCTION(BlueprintCallable)
	void RemoveCurrentItem();
	
	UFUNCTION(BlueprintPure, BlueprintCallable)
	class UBackpackItem* GetCurrentItem();
	
	UFUNCTION(BlueprintPure, BlueprintCallable)
	class UBackpackItem* GetNextItem();

	UFUNCTION(BlueprintPure, BlueprintCallable)
	int GetNextIndex() const;
	UFUNCTION(BlueprintPure, BlueprintCallable)
	int GetPrevIndex() const;

	UFUNCTION(BlueprintPure, BlueprintCallable)
	class UBackpackItem* GetPrevItem();

	UFUNCTION(BlueprintCallable)
	void MoveNext();

	UFUNCTION(BlueprintCallable)
	void MovePrev();

	void PostChangeCurrentItem();
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	TArray<FItemUIRepresentation> GetUiInfo() const;
	
	TArray<class UBackpackItem*> Items;
	int CurrentIndex {-1};

	UPROPERTY(BlueprintAssignable)
	FMoveBackpackUpDelegate OnMoveUp;

	UPROPERTY(BlueprintAssignable)
	FMoveBackpackDownDelegate OnMoveDown;
	
	UPROPERTY(BlueprintAssignable)
	FBackpackUpdate OnBackpackUpdate;
};
