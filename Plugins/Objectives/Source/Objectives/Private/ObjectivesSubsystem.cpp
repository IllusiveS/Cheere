// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectivesSubsystem.h"

#include "ObjectivesMainWidget.h"
#include "ObjectiveWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Image.h"

void UObjectivesSubsystem::Setup(AActor* Actor, TSubclassOf<UObjectivesMainWidget> MainClass)
{
	auto ObjWidget = CreateWidget<UObjectivesMainWidget>(Actor->GetWorld(), MainClass);
	ObjWidget->AddToViewport(-99);
	Parent = ObjWidget;
}

void UObjectivesSubsystem::AddObjective(AActor* Actor, UTexture2D* Widget, TSubclassOf<UObjectiveWidget> ObjectiveWidget, TSubclassOf<UObjectivesMainWidget> MainClass)
{
	if (Parent == nullptr)
	{
		Setup(Actor, MainClass);
	}
	auto ObjWidget = CreateWidget<UObjectiveWidget>(Actor->GetWorld(), ObjectiveWidget);
	ObjWidget->ObjectiveIcon->SetBrushFromTexture(Widget);
	ObjWidget->ActorToFollow = Actor;
	ObjWidget->AddToViewport(-99);
	
	//auto slot = Cast<UCanvasPanelSlot>(Parent->Canvas->AddChild(ObjWidget));
	//slot->SetSize({100.0f, 100.0f});
	
	ObjectiveWidgets.Add(Actor, ObjWidget);
}

void UObjectivesSubsystem::RemoveObjective(AActor* Actor)
{
	
}

void UObjectivesSubsystem::RemoveAllObjectives()
{
	for(auto Pair : ObjectiveWidgets)
	{
		Pair.Value->RemoveFromParent();
	}
	ObjectiveWidgets.Empty();
}
