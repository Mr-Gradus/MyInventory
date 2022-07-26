#pragma once

#include "CoreMinimal.h"
#include "InteractableObject.h"
#include "GameFramework/Actor.h"
#include "InteractedActor.generated.h"

UCLASS()
class MYQUESTMODULE_API AInteractedActor : public AActor, public IInteractableObject
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void OnInteractionFinished(AActor* InteractInstigator);
};
