// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class TopDownerEditorTarget : TargetRules
{
	public TopDownerEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_2;
		CppStandard = CppStandardVersion.Cpp20;
		CppStandardEngine = CppStandardVersion.Cpp20;
		ExtraModuleNames.Add("TopDowner");
		ExtraModuleNames.Add("TopDownerEditor");
	}
}
