// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <CoreMinimal.h>
#include <Blueprint/UserWidget.h>
#include "QuestDialog.generated.h"

class AQuest;
class UQuestDescription;
class UButton;

/**
 * 
 */
UCLASS()
class MYQUESTMODULE_API UQuestDialog : public UUserWidget
{
	GENERATED_BODY()

public:
	FSimpleDelegate OnQuestAccepted;
	
	FSimpleDelegate OnDialogClosed;

protected:
	UPROPERTY( meta = (BindWidget) )
	UQuestDescription* QuestDescription;
	
	UPROPERTY( meta = (BindWidget) )
	UButton* AcceptButton;
	
	UPROPERTY( meta = (BindWidget) )
	UButton* RejectButton;
	
public:
	void Init(AQuest* Quest);

	virtual void NativeConstruct() override;

protected:
	UFUNCTION()
	void OnAccepted();

	UFUNCTION()
	void OnRejected();

	void HideDialog();
	
};
