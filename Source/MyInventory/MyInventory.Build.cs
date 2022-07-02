// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MyInventory : ModuleRules
{
	public MyInventory(ReadOnlyTargetRules Target) : base(Target)
	{
		//PrivateDependencyModuleNames.AddRange(new string[] { "InventoryModule" });
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "NavigationSystem", "AIModule", "UMG", "Slate", "SlateCore", "InventoryModule" });
    }
}
