#include "QuestNpcManage.h"
#include "QuestManagerEdit.h"

#define LOCTEXT_NAMESPACE "FQuestNpcManageModule"

void FQuestNpcManageModule::StartupModule()
{
	FEditorModeRegistry::Get().RegisterMode<FQuestManagerEdit>(FQuestManagerEdit::EM_QuestNpcManageEdModeId, LOCTEXT("QuestNpcManageEdModeName", "QuestNpcManageEdMode"), FSlateIcon(), true);
}

void FQuestNpcManageModule::ShutdownModule()
{
	FEditorModeRegistry::Get().UnregisterMode(FQuestManagerEdit::EM_QuestNpcManageEdModeId);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FQuestNpcManageModule, QuestNpcManage)