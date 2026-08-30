using UnrealBuildTool;
using System.Collections.Generic;

public class SunkenCityTarget : TargetRules
{
	public SunkenCityTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.Latest;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		ExtraModuleNames.Add("SunkenCity");
	}
}
