// Copyright Epic Games, Inc. All Rights Reserved.

#include "TopDownerToolbarCommands.h"

#define LOCTEXT_NAMESPACE "FTestToolbarModule"

void FTopDownerEditorCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "TestToolbar", "Execute TestToolbar action", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
