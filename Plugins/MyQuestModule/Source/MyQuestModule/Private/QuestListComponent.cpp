#include "QuestListComponent.h"

UQuestListComponent::UQuestListComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

const TArray<AQuest*>& UQuestListComponent::GetQuests()
{
	return AcceptedQuests;
}

AQuest* UQuestListComponent::GetActiveQuest() const
{
	return ActiveQuest;
}

void UQuestListComponent::BeginPlay()
{
	Super::BeginPlay();

	if (CurrentObjectivesWidgetClass)
    {
	    UCurrentObjectives* CurrentObjectivesWidget = CreateWidget<UCurrentObjectives>(GetWorld(), CurrentObjectivesWidgetClass);
	    OnActiveQuestChanged.AddUObject(CurrentObjectivesWidget, &UCurrentObjectives::SetCurrentObjectives);
	    CurrentObjectivesWidget->AddToViewport();
    }

}

void UQuestListComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UQuestListComponent::AddQuest(AQuest* Quest)
{
	if (Quest == nullptr)
	{
		return;
	}	

	if (ActiveQuest == nullptr || ActiveQuest->IsCompleted())
	{
		ActiveQuest = Quest;
		
		OnActiveQuestChanged.Broadcast(ActiveQuest);		
	}
	
	if (Quest)
	{
		AcceptedQuests.AddUnique(Quest);
		Quest->TakeQuest(GetOwner());
		Quest->OnQuestStatusUpdated.AddLambda([this](AQuest* ChangedQuest )
		{
			if (ActiveQuest == ChangedQuest && OnActiveQuestChanged.IsBound())
			{
				OnActiveQuestChanged.Broadcast(ChangedQuest);
			}
		 });
		 
	} 
}

void UQuestListComponent::SetActiveQuest(AQuest* Quest)
{
	if (AcceptedQuests.Contains(Quest))
    {
	    ActiveQuest = Quest;
	    if (OnActiveQuestChanged.IsBound())
	    {
			OnActiveQuestChanged.Broadcast(Quest);
	    }
    }
}


