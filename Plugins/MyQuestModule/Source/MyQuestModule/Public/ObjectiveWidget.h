// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <CoreMinimal.h>
#include <Blueprint/UserWidget.h>
#include "ObjectiveWidget.generated.h"

class UObjective;
class UCheckBox;
class UTextBlock;

/**
 * 
 */
UCLASS()
class MYQUESTMODULE_API UObjectiveWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY( meta = (BindWidget) )
	UCheckBox* CompletedCheck;

	UPROPERTY( meta = (BindWidget) )
	UTextBlock* DescriptionText;
	
public:
	void Init(UObjective *Objective);
};
