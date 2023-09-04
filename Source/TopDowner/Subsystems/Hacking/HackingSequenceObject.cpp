// Fill out your copyright notice in the Description page of Project Settings.


#include "HackingSequenceObject.h"

void UHackingSequenceObject::AddBatteryPower(float PowerToAdd)
{
	CurrentPoints += PowerToAdd;
	OnHackingStatusChange.Broadcast(CurrentPoints, PointsRequired);
	if (CurrentPoints >= PointsRequired)
	{
		EndHacking();
	}
}

void UHackingSequenceObject::BeginHacking()
{
}

void UHackingSequenceObject::EndHacking()
{
	OnHackingFinished.Broadcast();
}
