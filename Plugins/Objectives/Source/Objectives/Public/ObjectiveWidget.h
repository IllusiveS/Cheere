// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ObjectiveWidget.generated.h"

/**
 * 
 */
UCLASS()
class OBJECTIVES_API UObjectiveWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	
	UPROPERTY(BlueprintReadOnly)
	class AActor* ActorToFollow;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	class UImage* ObjectiveIcon;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void UpdateVisibilityState();
	
	bool IsOnCorrectLayer {false};
	bool IsActive {true};

	UFUNCTION(BlueprintImplementableEvent)
	void OnShow();
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnHide();
};
