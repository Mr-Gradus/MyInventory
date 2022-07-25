#include "QuestDescription.h"

#include "Objective.h"
#include "ObjectiveWidget.h"
#include "Quest.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"

void UQuestDescription::Init(AQuest * Quest)
{
	if (Quest)
	{
		if (NameText)
		{
			//NameText->SetText(Quest->GetName());
		}
		if (DescriptionText)
		{
		//	DescriptionText->SetText(Quest->GetDescription());
		}
		if (ObjectiveWidgetClass && ObjectivesList)
		{
			ObjectivesList->ClearChildren();
			for (UObjective* Objective : Quest->GetObjectives())
			{
				UObjectiveWidget * ObjectiveWidget = CreateWidget<UObjectiveWidget>(this, ObjectiveWidgetClass);
				ObjectiveWidget->Init(Objective);
				ObjectivesList->AddChild(ObjectiveWidget);
			}
		}
	}
}


