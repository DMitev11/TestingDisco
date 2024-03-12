// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class Nano : ModuleRules
{
	public Nano(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "SteamCorePro" });
	}
}
