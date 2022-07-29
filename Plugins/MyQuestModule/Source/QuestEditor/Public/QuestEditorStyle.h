#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateStyle.h"

class FQuestEditorStyle
{
public:

	static void Initialize();

	static void Shutdown();

	static void ReloadTextures();

	static FName GetStyleSetName();

private:

	static const ISlateStyle& Get();


	static TSharedRef< class FSlateStyleSet > Create();

	static TSharedPtr< class FSlateStyleSet > StyleInstance;
};