// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Platformer_2_5D : ModuleRules
{
	public Platformer_2_5D(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
