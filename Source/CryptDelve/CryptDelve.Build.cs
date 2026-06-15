// Copyright CryptDelve. All Rights Reserved.

using UnrealBuildTool;

public class CryptDelve : ModuleRules
{
	public CryptDelve(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"GameplayAbilities",
			"GameplayTags",
			"GameplayTasks",
			"AIModule",
			"UMG",
			"Slate",
			"SlateCore",
			"CommonUI",
			"OnlineSubsystem",
			"OnlineSubsystemUtils",
			"HTTP",
			"Json",
			"JsonUtilities"
		});

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"OnlineSubsystemEOS"
		});

		PublicIncludePaths.AddRange(new string[]
		{
			"CryptDelve",
			"CryptDelve/Core",
			"CryptDelve/Characters",
			"CryptDelve/Abilities",
			"CryptDelve/Equipment",
			"CryptDelve/Progression",
			"CryptDelve/Roguelike",
			"CryptDelve/LevelGen",
			"CryptDelve/Network",
			"CryptDelve/UI"
		});
	}
}
