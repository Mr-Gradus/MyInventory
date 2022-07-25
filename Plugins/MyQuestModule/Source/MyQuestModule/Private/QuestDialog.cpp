
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

	if (RejectButton)
	{
		RejectButton->OnReleased.AddDynamic(this, &UQuestDialog::RejectQuest);
	}

	APlayerController * PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(PC);
	PC->bShowMouseCursor = true;

}


void UQuestDialog::AcceptQuest()
{
	HideDialog();
	OnQuestAccepted.ExecuteIfBound();
}

void UQuestDialog::RejectQuest()
{
	HideDialog();
}

void UQuestDialog::HideDialog()
{
	RemoveFromViewport();

	APlayerController * PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	UWidgetBlueprintLibrary::SetInputMode_GameOnly(PC);
	PC->bShowMouseCursor = false;

	OnQuestQuited.ExecuteIfBound();
}





