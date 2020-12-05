// Copyright BBAGWANG SOFT, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TheDay : ModuleRules
{
	public TheDay(ReadOnlyTargetRules Target) : base(Target)
	{
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PrivateIncludePaths.Add(ModuleDirectory);
        PublicIncludePaths.Add(ModuleDirectory);

        //PrivatePCHHeaderFile = "TheDay.h";

        PublicDependencyModuleNames.AddRange(new string[]
        { "Core", "CoreUObject", "Engine", "InputCore",
        "GameplayAbilities","GameplayTags","GameplayTasks",
        "NavigationSystem","AIModule", "Slate", "SlateCore",
        "UMG"});
    }
}
