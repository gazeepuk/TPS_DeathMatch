// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ShootyBooty : ModuleRules
{
	public ShootyBooty(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "GameplayTasks", "NavigationSystem", "EnhancedInput" });

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[]
		{
			"ShootyBooty/Public",
			"ShootyBooty/Public/Characters",
			"ShootyBooty/Public/Components",
			"ShootyBooty/Public/Dev",
			"ShootyBooty/Public/Weapon",
			"ShootyBooty/Public/UI",
			"ShootyBooty/Public/Animations",
			"ShootyBooty/Public/Pickup",
			"ShootyBooty/Public/AI",
			"ShootyBooty/Public/AI/Tasks",
			"ShootyBooty/Public/AI/Services",
			"ShootyBooty/Public/AI/EQS",
			"ShootyBooty/Public/AI/Decorators"
		});
		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}