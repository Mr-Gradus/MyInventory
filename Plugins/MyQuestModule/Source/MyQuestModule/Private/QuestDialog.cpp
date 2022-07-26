
#include "QuestDialog.h"
#include "Quest.h"
#include "QuestDescription.h"
#include <Components/Button.h>
#include <Kismet/GameplayStatics.h>
#include <Blueprint/WidgetBlueprintLibrary.h>

void UQuestDialog::Init(AQuest* Quest) const
{
	if (Description)
    {
		Description->Init(Quest);
    }

}

void UQuestDialog::NativeConstruct()
{
	Super::NativeConstruct();

	if (AcceptButton)
	{
		AcceptButton->OnReleased.AddDynamic(this, &UQuestDialog::AcceptQuest);
	}

	if (CancelButton)
	{
		CancelButton->OnReleased.AddDynamic(this, &UQuestDialog::CancelQuest);
	}

	APlayerController * PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(PC);
	PC->bShowMouseCursor = true;

}


void UQuestDialog::AcceptQuest()
{
	HideDialog();
	if (OnQuestAccepted.IsBound())
	{
		OnQuestAccepted.Broadcast();
	}
}

void UQuestDialog::CancelQuest()
{
	HideDialog();
}

void UQuestDialog::HideDialog()
{
	RemoveFromViewport();

	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	UWidgetBlueprintLibrary::SetInputMode_GameOnly(PC);
	PC->bShowMouseCursor = false;

	OnQuestQuited.ExecuteIfBound();
}





