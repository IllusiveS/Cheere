// Fill out your copyright notice in the Description page of Project Settings.


#include "BackpackComponent.h"

#include "BackpackItem.h"

// Sets default values for this component's properties
UBackpackComponent::UBackpackComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBackpackComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBackpackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

UBackpackItem* UBackpackComponent::GetCurrentItem()
{
	if (Items.IsEmpty()) return nullptr;

	return Items[CurrentIndex];
}

UBackpackItem* UBackpackComponent::GetNextItem()
{
	if (Items.IsEmpty()) return nullptr;
	const int DesiredIndex = (CurrentIndex + 1) % Items.Num();
	return Items[DesiredIndex];
}

UBackpackItem* UBackpackComponent::GetPrevItem()
{
	if (Items.IsEmpty()) return nullptr;
	const int DesiredIndex = (CurrentIndex - 1) >= 0 ? CurrentIndex - 1 : Items.Num() - 1;
	return Items[DesiredIndex];
}

void UBackpackComponent::MoveNext()
{
	CurrentIndex = (CurrentIndex + 1) % Items.Num();
	OnMoveUp.Broadcast();
	OnBackpackUpdate.Broadcast(Items, CurrentIndex);
}

void UBackpackComponent::MovePrev()
{
	CurrentIndex = (CurrentIndex - 1) >= 0 ? CurrentIndex - 1 : Items.Num() - 1;
	OnMoveDown.Broadcast();
	OnBackpackUpdate.Broadcast(Items, CurrentIndex);
}

