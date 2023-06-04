// Fill out your copyright notice in the Description page of Project Settings.


#include "BackpackItem.h"

FItemUIRepresentation UBackpackItem::GetUIStruct() const
{
	auto ItemRep = FItemUIRepresentation{};
	ItemRep.Amount = Amount;
	ItemRep.ItemAsset = ItemAsset;

	return ItemRep;
}
