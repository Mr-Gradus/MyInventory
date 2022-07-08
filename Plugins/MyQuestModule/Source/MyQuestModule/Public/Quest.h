
#pragma once

#include "CoreMinimal.h"
#include "Objective.h"
#include "GameFramework/Actor.h"
#include "Quest.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnQuestStatusUpdated, AActor*)

UCLASS()
class MYQUESTMODULE_API AQuest : public AActor
{
	GENERATED_BODY()
	
public:	
	AQuest();

	void TakeQuest(AActor* Character);

	FOnQuestStatusUpdated OnQuestStatusUpdated;
	
	UFUNCTION(BlueprintPure)
	const TArray<UObjective*>& GetObjectives() const { return Objectives; }

protected:
	virtual void BeginPlay() override;

	void OnObjectiveCompleted(UObjective* Objective);

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, CallInEditor)
	void UpdateLocation();

	UFUNCTION(BlueprintCallable, CallInEditor)
	void AddLocationObjective();

	UFUNCTION(BlueprintCallable, CallInEditor)
	void AddInteractObjective();

	UPROPERTY(EditAnywhere)
	FText Name;
	
	UPROPERTY(EditAnywhere)
	FText Description;

	UPROPERTY(EditAnywhere)
	TArray<UObjective*> Objectives;

	UPROPERTY(EditAnywhere)
	bool bIsStoryQuest = true;

	UPROPERTY(EditAnywhere)
	bool bKeepObjectivesOrder = true;
	
	UPROPERTY(EditAnywhere)
	bool bIsTaken;

	UPROPERTY(EditAnywhere)
	AQuest* PrerequisitedQuest;
};
