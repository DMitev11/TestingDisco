// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class NanoTarget : TargetRules
{
	public NanoTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V4;
		bUsesSteam = true;

		ExtraModuleNames.AddRange(new string[] { "Nano" });
	}
}
