#pragma once

#include "CoreMinimal.h"
#include "QuestDescription.h"
#include "QuestListComponent.h"
#include "QuestListEntry.h"
#include "Blueprint/UserWidget.h"
#include "Components/ScrollBox.h"
#include "QuestList.generated.h"

UCLASS()
class MYQUESTMODULE_API UQuestList : public UUserWidget
{
	GENERATED_BODY()

public:

	void Init(UQuestListComponent* QuestList);

protected:
	UPROPERTY(meta = (BindWidgetOptional))
	UScrollBox* StoryQuestsList;
	
	UPROPERTY(meta = (BindWidgetOptional))
	UScrollBox* SideQuestsList;
	
	UPROPERTY(meta = (BindWidgetOptional))
	UQuestDescription* ActiveQuestDescription;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UQuestListEntry> QuestEntryClass;
	
	UPROPERTY()
	TMap<AQuest*, UQuestListEntry*> QuestEntries;
	
	void OnActiveQuestChanged(AQuest* ActiveQuest);
};
