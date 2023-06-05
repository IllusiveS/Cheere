// Fill out your copyright notice in the Description page of Project Settings.


#include "BackpackComponent.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "BackpackItem.h"
#include "TopDowner/GAS/TopDownerGameplayEffect.h"

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

bool UBackpackComponent::CanPickupItem(UBackpackItemAsset* ItemToPickUp) const
{
	const auto i = 1;
	//Do i have the item?
	const auto Result = Items.FindByPredicate([&ItemToPickUp](const auto& Item)
	{
		return Item->ItemAsset == ItemToPickUp;
	});
	
	if (Result == nullptr) return true;

	const auto ActualResult = *Result;
	return ActualResult->Amount < ActualResult->ItemAsset->MaxAmount;
}

void UBackpackComponent::PickupItem(UBackpackItemAsset* ItemToPickUp)
{
	const auto Result = Items.FindByPredicate([&ItemToPickUp](const auto& Item)
	{
		return Item->ItemAsset == ItemToPickUp;
	});
	
	if (Result == nullptr)
	{
		auto NewItem = NewObject<UBackpackItem>();
		NewItem->ItemAsset = ItemToPickUp;
		NewItem->Amount = 1;

		if (CurrentIndex == -1)
		{
			CurrentIndex = 0;
		}
		Items.Add(NewItem);
	} else
	{
		const auto ActualResult = *Result;
		ActualResult->Amount++;
	}
	
	PostChangeCurrentItem();
}

void UBackpackComponent::RemoveCurrentItem()
{
	if (Items[CurrentIndex]->Amount == 1)
	{
		Items.RemoveAt(CurrentIndex);
	} else
	{
		Items[CurrentIndex]->Amount--;
	}
	PostChangeCurrentItem();
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

int UBackpackComponent::GetNextIndex() const
{
	if (Items.IsEmpty()) return -1;
	const int DesiredIndex = (CurrentIndex + 1) % Items.Num();
	return DesiredIndex;
}

int UBackpackComponent::GetPrevIndex() const
{
	if (Items.IsEmpty()) return -1;
	const int DesiredIndex = (CurrentIndex - 1) >= 0 ? CurrentIndex - 1 : Items.Num() - 1;
	return DesiredIndex;
}

UBackpackItem* UBackpackComponent::GetPrevItem()
{
	if (Items.IsEmpty()) return nullptr;
	const int DesiredIndex = (CurrentIndex - 1) >= 0 ? CurrentIndex - 1 : Items.Num() - 1;
	return Items[DesiredIndex];
}

void UBackpackComponent::MoveNext()
{
	if (Items.IsEmpty()) return;
	CurrentIndex = (CurrentIndex + 1) % Items.Num();
	OnMoveUp.Broadcast();
	PostChangeCurrentItem();
}

void UBackpackComponent::MovePrev()
{
	if (Items.IsEmpty()) return;
	CurrentIndex = (CurrentIndex - 1) >= 0 ? CurrentIndex - 1 : Items.Num() - 1;
	OnMoveDown.Broadcast();
	PostChangeCurrentItem();
}

void UBackpackComponent::PostChangeCurrentItem()
{
	const auto AbilityInterface = Cast<IAbilitySystemInterface>(GetOwner());
	ensure(AbilityInterface != nullptr);

	if (auto CurrentItem = GetCurrentItem())
	{
		const auto AbilityComponent = AbilityInterface->GetAbilitySystemComponent();
		const auto Context = AbilityComponent->MakeEffectContext();
		AbilityComponent->ApplyGameplayEffectToSelf(CurrentItem->ItemAsset->EffectToApplyWhenEquipped.GetDefaultObject(), 1.0, Context);
	}
	else
	{
		CurrentIndex = -1;
	}

	const auto UIInfos = GetUiInfo();
	const auto NextIndex = GetNextIndex();
	const auto PrevIndex = GetPrevIndex();

	OnBackpackUpdate.Broadcast(UIInfos, CurrentIndex, NextIndex, PrevIndex);
}

TArray<FItemUIRepresentation> UBackpackComponent::GetUiInfo() const
{
	TArray<FItemUIRepresentation> ItemsToReturn;

	for(const auto& item : Items) {
		ItemsToReturn.Push(item->GetUIStruct());
	}

	return ItemsToReturn;
}

