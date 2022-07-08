// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objective.h"
#include "GameFramework/Actor.h"
#include "Quest.generated.h"

UCLASS()
class MYQUESTMODULE_API AQuest : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AQuest();

	void TakeQuest(AActor * Character);

	UFUNCTION(BlueprintPure)
	const TArray<UObjective*>& GetObjectives() const { return Objectives; }

	UFUNCTION(BlueprintPure)
	FText GetQuestName() const { return Name; }
	
	UFUNCTION(BlueprintPure)
	FText GetQuestDescription() const { return Description; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	FText Name;
	
	UPROPERTY(EditAnywhere)
	FText Description;

	UPROPERTY(EditAnywhere)
	TArray<UObjective*> Objectives;

	UPROPERTY(EditAnywhere)
	bool bIsStoryQuest;

	UPROPERTY(EditAnywhere)
	bool bKeepObjectivesOrder;
	
	UPROPERTY(EditAnywhere)
	bool bIsTaken;

	UPROPERTY(EditAnywhere)
	AQuest* PrerequisiteQuest;
};
