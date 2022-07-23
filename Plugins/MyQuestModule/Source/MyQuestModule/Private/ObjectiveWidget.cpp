#include "ObjectiveWidget.h"
#include "Objective.h"
#include "Components/CheckBox.h"
#include "Components/TextBlock.h"

void UObjectiveWidget::Init(UObjective* Objective)
{
	if (Objective)
    {
	    if (ComplitedCheck)
	    {
			ComplitedCheck->SetIsChecked(Objective->bIsCompleted);
	    }
	    if (DescriptionText)
	    {
			DescriptionText->SetText(Objective->Description);
	    }
    }

}
