// Copyright BBAGWANG SOFT, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class TheDayEditorTarget : TargetRules
{
	public TheDayEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.Add("TheDay");
	}
}
