// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeDilationSlowdownSubsystem.h"

#include "Kismet/GameplayStatics.h"

void UTimeDilationSlowdownSubsystem::SetAimingSlowTime(float DilationAmount)
{
	CurrentAimingSlowdown = DilationAmount;
}

void UTimeDilationSlowdownSubsystem::SlowTime(float DilationAmount, float DilationTime, bool ForceNew, TEnumAsByte<ESlowdownType> SlowdownType)
{
	if (GetWorld()->GetTimerManager().IsTimerActive(CurrentSlowdownHandle))
	{
		if (SlowdownType >= CurrentSlowdown && ForceNew == false) return;
		
		GetWorld()->GetTimerManager().ClearTimer(CurrentSlowdownHandle);
	}

	const auto TimerScaledTime = DilationTime * DilationAmount * CurrentAimingSlowdown;
	GetWorld()->GetTimerManager().SetTimer(CurrentSlowdownHandle, this, &UTimeDilationSlowdownSubsystem::OnSlowTimeEnded, TimerScaledTime);
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), DilationAmount);

	CurrentSlowdownAmount = DilationAmount * CurrentAimingSlowdown;
	CurrentSlowdown = SlowdownType;
}

void UTimeDilationSlowdownSubsystem::OnSlowTimeEnded()
{
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), CurrentAimingSlowdown);
	GetWorld()->GetTimerManager().ClearTimer(CurrentSlowdownHandle);
}
