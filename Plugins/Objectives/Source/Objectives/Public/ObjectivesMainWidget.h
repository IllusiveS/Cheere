// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ObjectivesMainWidget.generated.h"

/**
 * 
 */
UCLASS()
class OBJECTIVES_API UObjectivesMainWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta=(BindWidget))
	class UCanvasPanel* Canvas;
};
