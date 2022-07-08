// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <CoreMinimal.h>
#include <Blueprint/UserWidget.h>
#include "QuestDescription.generated.h"

class AQuest;
class UObjectiveWidget;
class UTextBlock;
class UScrollBox;

/**
 * 
 */
UCLASS()
class MYQUESTMODULE_API UQuestDescription : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY( meta = (BindWidget) )
	UTextBlock* NameText;

	UPROPERTY( meta = (BindWidget) )
	UTextBlock* DescriptionText;

	UPROPERTY( meta = (BindWidget) )
	UScrollBox* ObjectivesList;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UObjectiveWidget> ObjectiveWidgetClass;

public:
	void Init(AQuest *Quest);
	
};
