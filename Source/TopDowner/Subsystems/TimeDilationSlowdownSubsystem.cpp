// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeDilationSlowdownSubsystem.h"

#include "Kismet/GameplayStatics.h"

void UTimeDilationSlowdownSubsystem::SlowTime(float DilationAmount, float DilationTime, bool ForceNew)
{
	if (GetWorld()->GetTimerManager().IsTimerActive(CurrentSlowdownHandle))
	{
		if (CurrentSlowdownAmount >= DilationAmount && ForceNew == false) return;
		
		GetWorld()->GetTimerManager().ClearTimer(CurrentSlowdownHandle);
	}

	const auto TimerScaledTime = DilationTime * DilationAmount;
	GetWorld()->GetTimerManager().SetTimer(CurrentSlowdownHandle, this, &UTimeDilationSlowdownSubsystem::OnSlowTimeEnded, TimerScaledTime);
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), DilationAmount);

	CurrentSlowdownAmount = DilationAmount;
}

void UTimeDilationSlowdownSubsystem::OnSlowTimeEnded()
{
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.0);
	GetWorld()->GetTimerManager().ClearTimer(CurrentSlowdownHandle);
}
