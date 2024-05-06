// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectiveWidget.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Kismet/GameplayStatics.h"

void UObjectiveWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	UpdateVisibilityState();
	// auto Controller = UGameplayStatics::GetPlayerController(this, 0);
	// FVector2d Pos;
	// Controller->ProjectWorldLocationToScreen(ActorToFollow->GetActorLocation(), Pos);
	//
	// auto ViewportSize = UWidgetLayoutLibrary::GetViewportSize(this);
	// auto WidgetSize = GetDesiredSize() / 2.0f;
	//
	// auto Size = WidgetSize - ViewportSize;
	//
	// auto ClampedSize = FVector2D(
	// 	FMath::Clamp(Pos.X, 0.0f, Size.X),
	// 	FMath::Clamp(Pos.Y, 0.0f, Size.Y)
	// );
	//
	// SetPositionInViewport(ClampedSize);
}

void UObjectiveWidget::UpdateVisibilityState()
{
	const auto NewVisibilityState = IsOnCorrectLayer && IsActive ? ESlateVisibility::Visible : ESlateVisibility::Hidden;
	if(NewVisibilityState != GetVisibility())
	{
		if(NewVisibilityState == ESlateVisibility::Visible)
		{
			OnShow();
		}
		else
		{
			OnHide();
		}
		SetVisibility(NewVisibilityState);
	}
}
