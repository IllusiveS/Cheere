// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeDilationSlowdownSubsystem.h"

#include "Kismet/GameplayStatics.h"

void UTimeDilationSlowdownSubsystem::SetAimingSlowTime(float DilationAmount)
{
	CurrentAimingSlowdown = DilationAmount;
}

void UTimeDilationSlowdownSubsystem::SlowTime(float DilationAmount, float DilationTime, bool ForceNew)
{
	if (GetWorld()->GetTimerManager().IsTimerActive(CurrentSlowdownHandle))
	{
		if (CurrentSlowdownAmount >= DilationAmount && ForceNew == false) return;
		
		GetWorld()->GetTimerManager().ClearTimer(CurrentSlowdownHandle);
	}

	const auto TimerScaledTime = DilationTime * DilationAmount * CurrentAimingSlowdown;
	GetWorld()->GetTimerManager().SetTimer(CurrentSlowdownHandle, this, &UTimeDilationSlowdownSubsystem::OnSlowTimeEnded, TimerScaledTime);
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), DilationAmount);

	CurrentSlowdownAmount = DilationAmount * CurrentAimingSlowdown;
}

void UTimeDilationSlowdownSubsystem::OnSlowTimeEnded()
{
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.0);
	GetWorld()->GetTimerManager().ClearTimer(CurrentSlowdownHandle);
}
