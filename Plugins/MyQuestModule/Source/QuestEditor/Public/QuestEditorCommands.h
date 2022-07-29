#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "QuestEditorStyle.h"

class FQuestEditorCommands : public TCommands<FQuestEditorCommands>
{
public:

	FQuestEditorCommands() : TCommands<FQuestEditorCommands>( TEXT("QuestEditor"), 
	NSLOCTEXT("Contexts", "QuestEditor", "QuestEditor Plugin"), NAME_None, FQuestEditorStyle::GetStyleSetName()){}

	virtual void RegisterCommands() override;
	
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};