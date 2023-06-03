// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BackpackComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMoveBackpackUpDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMoveBackpackDownDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBackpackUpdate, TArray<class UBackpackItem*>, Items, int, CurrentItem);

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

	UFUNCTION(BlueprintPure, BlueprintCallable)
	class UBackpackItem* GetCurrentItem();
	
	UFUNCTION(BlueprintPure, BlueprintCallable)
	class UBackpackItem* GetNextItem();

	UFUNCTION(BlueprintPure, BlueprintCallable)
	class UBackpackItem* GetPrevItem();

	UFUNCTION(BlueprintCallable)
	void MoveNext();

	UFUNCTION(BlueprintCallable)
	void MovePrev();
	
	TArray<class UBackpackItem*> Items;
	int CurrentIndex;

	UPROPERTY(BlueprintAssignable)
	FMoveBackpackUpDelegate OnMoveUp;

	UPROPERTY(BlueprintAssignable)
	FMoveBackpackDownDelegate OnMoveDown;
	
	UPROPERTY(BlueprintAssignable)
	FBackpackUpdate OnBackpackUpdate;
};
