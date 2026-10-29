using UnrealBuildTool;

public class MaxPayne2UnrealEditorTarget : TargetRules
{
    public MaxPayne2UnrealEditorTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Editor;
        DefaultBuildSettings = BuildSettingsVersion.V5;
        IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_4;
        ExtraModuleNames.Add("MaxPayne2Unreal");
    }
}
