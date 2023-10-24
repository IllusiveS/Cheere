// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectivesSubsystem.h"

#include "ObjectiveWidget.h"
#include "Algo/RemoveIf.h"
#include "Components/Image.h"
#include "Logging/StructuredLog.h"

DEFINE_LOG_CATEGORY(LogObjectives);

int UObjectivesSubsystem::GetCurrentLayer() const
{
	return CurrentLayer - 1;
}

void UObjectivesSubsystem::SetLayer(int NewLayer)
{
	UE_LOGFMT(LogObjectives, Log, "Setting layer to {1}", NewLayer);
	if (ObjectiveWidgets.IsValidIndex(GetCurrentLayer()))
	{
		for (const auto &Data : ObjectiveWidgets[GetCurrentLayer()].Objectives)
		{
			UE_LOGFMT(LogObjectives, Log, "Disabling correct layer on actor {1}", Data.TargetActor->GetName());
			Data.ObjectiveWidget->IsOnCorrectLayer = false;
			Data.ObjectiveWidget->UpdateVisibilityState();
		}
	}
	
	CurrentLayer = NewLayer;

	if (ObjectiveWidgets.IsValidIndex(GetCurrentLayer()))
	{
		for (const auto &Data : ObjectiveWidgets[GetCurrentLayer()].Objectives)
		{
			UE_LOGFMT(LogObjectives, Log, "Enabling correct layer on actor {1}", Data.TargetActor->GetName());
			Data.ObjectiveWidget->IsOnCorrectLayer = true;
			Data.ObjectiveWidget->UpdateVisibilityState();
		}
	}
}

void UObjectivesSubsystem::PushLayer()
{
	SetLayer(CurrentLayer + 1);
	ObjectiveWidgets.Emplace();
}

void UObjectivesSubsystem::PopLayer()
{
	for (const auto &Data : ObjectiveWidgets[GetCurrentLayer()].Objectives)
	{
		Data.ObjectiveWidget->IsOnCorrectLayer = false;
		Data.ObjectiveWidget->RemoveFromParent();
	}
	SetLayer(CurrentLayer - 1);
	ObjectiveWidgets.Pop();
}

void UObjectivesSubsystem::AddObjective(AActor* Actor, UTexture2D* Widget, TSubclassOf<UObjectiveWidget> ObjectiveWidget)
{
	auto ObjWidget = CreateWidget<UObjectiveWidget>(Actor->GetWorld(), ObjectiveWidget);
	ObjWidget->ObjectiveIcon->SetBrushFromTexture(Widget);
	ObjWidget->ActorToFollow = Actor;
	ObjWidget->AddToViewport(-99);
	ObjWidget->IsOnCorrectLayer = true;
	
	//auto slot = Cast<UCanvasPanelSlot>(Parent->Canvas->AddChild(ObjWidget));
	//slot->SetSize({100.0f, 100.0f});
	FObjectiveDataStruct Data;
	Data.ObjectiveWidget = ObjWidget;
	Data.TargetActor = Actor;
	Data.Layer = CurrentLayer;
	
	AddToWidgetsMap(Data);

	Actor->OnDestroyed.AddUniqueDynamic(this, &UObjectivesSubsystem::RemoveObjective);
}

void UObjectivesSubsystem::RemoveObjective(AActor* Actor)
{
	for (auto &Data : ObjectiveWidgets)
	{
		Data.Objectives.RemoveAll([&Actor](const FObjectiveDataStruct &DataStruct)
		{
			return Actor == DataStruct.TargetActor;
		});
	}
}

void UObjectivesSubsystem::MakeObjectiveActive(AActor* Actor)
{
	for (auto &Layer : ObjectiveWidgets)
	{
		for (auto &LayerData : Layer.Objectives)
		{
			if (LayerData.TargetActor == Actor)
			{
				LayerData.ObjectiveWidget->IsActive = true;
				LayerData.ObjectiveWidget->UpdateVisibilityState();
				UE_LOGFMT(LogObjectives, Log, "Making objective active on actor {1}", LayerData.TargetActor->GetName());
			}
		}
	}
}

void UObjectivesSubsystem::MakeObjectiveUnactive(AActor* Actor)
{
	for (auto &Layer : ObjectiveWidgets)
	{
		for (auto &LayerData : Layer.Objectives)
		{
			if (LayerData.TargetActor == Actor)
			{
				LayerData.ObjectiveWidget->IsActive = false;
				LayerData.ObjectiveWidget->UpdateVisibilityState();
				UE_LOGFMT(LogObjectives, Log, "Making objective unactive on actor {1}", LayerData.TargetActor->GetName());
			}
		}
	}
}

void UObjectivesSubsystem::AddToWidgetsMap(const FObjectiveDataStruct &Data)
{
	auto &Layer = ObjectiveWidgets[GetCurrentLayer()];
	Layer.Objectives.Emplace(Data);
}

void UObjectivesSubsystem::RemoveAllObjectives()
{
	unimplemented();
	// for(const auto &Data : ObjectiveWidgets)
	// {
	// 	Data.ObjectiveWidget->RemoveFromParent();
	// }
	// ObjectiveWidgets.Empty();
}
