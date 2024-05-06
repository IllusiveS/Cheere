// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TopDownerEditor : ModuleRules
{
	public TopDownerEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[]
        {
	        "Core"
	        , "CoreUObject"
	        , "Engine"
	        , "TopDowner"
	        , "GameplayTags"
	        , "Flow"
	        , "Slate"
	        , "SlateCore"
	        , "UnrealEd"
	        , "ToolMenus"
	        , "Projects"
        });
    }
}
