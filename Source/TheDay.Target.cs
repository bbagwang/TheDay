// Copyright BBAGWANG SOFT, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class TheDayTarget : TargetRules
{
	public TheDayTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.Add("TheDay");
	}
}
