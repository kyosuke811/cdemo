using UnrealBuildTool;

public class SunkenCity : ModuleRules
{
	public SunkenCity(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"UMG",
			"Niagara",
			"PhysicsCore"
		});

		PrivateDependencyModuleNames.AddRange(new string[] {
			"Slate",
			"SlateCore"
		});
	}
}
