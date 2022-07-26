#pragma once

#include <CoreMinimal.h>
#include <Blueprint/UserWidget.h>
#include "Quest.h"
#include "QuestDialog.generated.h"

class UQuestDescription;
class UButton;

DECLARE_MULTICAST_DELEGATE(FOnQuestAccepted);

UCLASS()
class MYQUESTMODULE_API UQuestDialog : public UUserWidget
{
	GENERATED_BODY()

public:
	FOnQuestAccepted OnQuestAccepted;
	
	FSimpleDelegate OnQuestQuited;

protected:
	UPROPERTY( meta = (BindWidgetOptional))
	UQuestDescription* Description;
	
	UPROPERTY( meta = (BindWidgetOptional))
	UButton* AcceptButton;
	
	UPROPERTY( meta = (BindWidgetOptional))
	UButton* CancelButton;
	
public:
	void Init(AQuest* Quest) const;

	virtual void NativeConstruct() override;

protected:
	UFUNCTION()
	void AcceptQuest();

	UFUNCTION()
	void CancelQuest();

	void HideDialog();
	
};
