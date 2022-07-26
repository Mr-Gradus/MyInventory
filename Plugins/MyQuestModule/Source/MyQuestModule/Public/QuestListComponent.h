#pragma once

#include "CoreMinimal.h"
#include "CurrentObjectives.h"
#include "Quest.h"
#include "Components/ActorComponent.h"
#include "QuestListComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MYQUESTMODULE_API UQuestListComponent : public UActorComponent
{
	GENERATED_BODY()

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnQuestAction, AQuest*);
	
public:

	UQuestListComponent();

	const TArray<AQuest*>& GetQuests();

	AQuest* GetActiveQuest() const;

	FOnQuestAction OnActiveQuestChanged;

protected:
	virtual void BeginPlay() override;
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	UPROPERTY()
	TArray<AQuest*> AcceptedQuests;
	
	UPROPERTY()
	AQuest* ActiveQuest;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UCurrentObjectives> CurrentObjectivesWidgetClass;

public:	
	void AddQuest(AQuest* Quest);

	void SetActiveQuest(AQuest* Quest);

};
