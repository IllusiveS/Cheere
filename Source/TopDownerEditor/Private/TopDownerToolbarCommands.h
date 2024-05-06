// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "TopDownerEditorStyle.h"

class FTopDownerEditorCommands : public TCommands<FTopDownerEditorCommands>
{
public:

	FTopDownerEditorCommands()
		: TCommands<FTopDownerEditorCommands>(TEXT("TestToolbar"), NSLOCTEXT("Contexts", "TestToolbar", "TestToolbar Plugin"), NAME_None, FTopDownerEditorStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
};
