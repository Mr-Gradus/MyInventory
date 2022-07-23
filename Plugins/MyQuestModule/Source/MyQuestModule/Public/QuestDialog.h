#pragma once

#include <CoreMinimal.h>
#include <Blueprint/UserWidget.h>
#include "QuestDialog.generated.h"

class AQuest;
class UQuestDescription;
class UButton;

UCLASS()
class MYQUESTMODULE_API UQuestDialog : public UUserWidget
{
	GENERATED_BODY()

public:
	FSimpleDelegate OnQuestAccepted;
	
	FSimpleDelegate OnQuestQuited;

protected:
	UPROPERTY( meta = (BindWidgetOptional))
	UQuestDescription* Description;
	
	UPROPERTY( meta = (BindWidgetOptional))
	UButton* AcceptButton;
	
	UPROPERTY( meta = (BindWidgetOptional))
	UButton* RejectButton;
	
public:
	void Init(AQuest* Quest) const;

	virtual void NativeConstruct() override;

protected:
	UFUNCTION()
	void AcceptQuest();

	UFUNCTION()
	void RejectQuest();

	void HideDialog();
	
};
