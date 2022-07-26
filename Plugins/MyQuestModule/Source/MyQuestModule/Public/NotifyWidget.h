#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "NotifyWidget.generated.h"

UCLASS()
class MYQUESTMODULE_API UNotifyWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(meta = (BindWidgetOptional))
	UImage* NotifyImage;

};
