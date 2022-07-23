#pragma once

#include <CoreMinimal.h>
#include <Blueprint/UserWidget.h>
#include "QuestDescription.generated.h"

class AQuest;
class UObjectiveWidget;
class UTextBlock;
class UScrollBox;

UCLASS()
class MYQUESTMODULE_API UQuestDescription : public UUserWidget
{
	GENERATED_BODY()

public:
	void Init(AQuest* Quest);

protected:
	UPROPERTY( meta = (BindWidgetOptional) )
	UTextBlock* NameText;

	UPROPERTY( meta = (BindWidgetOptional) )
	UTextBlock* DescriptionText;

	UPROPERTY( meta = (BindWidgetOptional) )
	UScrollBox* ObjectivesList;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UObjectiveWidget> ObjectiveWidgetClass;
};
