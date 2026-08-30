using UnrealBuildTool;
using System.Collections.Generic;

public class SunkenCityEditorTarget : TargetRules
{
	public SunkenCityEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.Latest;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		ExtraModuleNames.Add("SunkenCity");
	}
}
