#pragma once

#include "CoreMinimal.h"
#include "InteractableObject.h"
#include "NotifyWidget.h"
#include "QuestDialog.h"
#include "GameFramework/Pawn.h"
#include "Npc.generated.h"

UCLASS()
class MYQUESTMODULE_API ANpc : public APawn, public IInteractableObject
{
	GENERATED_BODY()

public:
	ANpc();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category ="Components")
	UStaticMeshComponent* Body;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category ="Components")
	UStaticMeshComponent* Head;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UQuestDialog> QuestDialogClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Components")
	TSubclassOf<UNotifyWidget> NotifyWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UWidgetComponent* NotifyWidget;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Interact_Implementation(AActor* InteractInstigator) override;

	TArray<AQuest*> GetQuests() const;

	TArray<AActor*> GetAllObjectiveComps() const;

	bool HasQuests() const;

	UFUNCTION()
	void GetAcceptableQuest();

	UFUNCTION()
	void SetHiddenNotificationWidget(bool bSetHidden) const;
};
