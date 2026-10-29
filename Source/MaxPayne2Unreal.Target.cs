using UnrealBuildTool;

public class MaxPayne2UnrealTarget : TargetRules
{
    public MaxPayne2UnrealTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Game;
        DefaultBuildSettings = BuildSettingsVersion.V5;
        IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_4;
        ExtraModuleNames.Add("MaxPayne2Unreal");
    }
}
