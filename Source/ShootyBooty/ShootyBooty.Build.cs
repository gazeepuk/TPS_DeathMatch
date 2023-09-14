// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ShootyBooty : ModuleRules
{
	public ShootyBooty(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[]
		{
			"ShootyBooty/Public/Player",
			"ShootyBooty/Public/Components",
			"ShootyBooty/Public/Dev",
			"ShootyBooty/Public/Weapon",
			"ShootyBooty/Public/UI",
			"ShootyBooty/Public/Animations"
		});
		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}