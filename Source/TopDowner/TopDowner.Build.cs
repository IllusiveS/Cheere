// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TopDowner : ModuleRules
{
	public TopDowner(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "NavigationSystem", "AIModule", "Niagara", "GameplayTasks", "EnhancedInput", "GameplayAbilities", "GameplayTags", "MotionWarping" });
    }
}
