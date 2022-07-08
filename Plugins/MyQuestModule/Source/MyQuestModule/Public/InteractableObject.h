#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractableObject.generated.h"

//class AInteractableActor;
UINTERFACE(MinimalAPI)
class UInteractableObject : public UInterface
{
	GENERATED_BODY()
};

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnInteractionFinished, AActor* /*InteractableObject*/, AActor* /*ActorInteractedWithObject*/);

class MYQUESTMODULE_API IInteractableObject
{
	GENERATED_BODY()


public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Interact(AActor* ActorInteractedWithObject);
	UFUNCTION()
	virtual void Interact_Implementation(AActor* ActorInteractedWithObject) {}

	virtual void NotifyInteractionFinished(AActor* InteractableObject, AActor* ActorInteractedWithObject)
	{
		if (OnInteractionFinished.IsBound())
		{
			OnInteractionFinished.Broadcast(InteractableObject,
			ActorInteractedWithObject);
		}
	}
	FOnInteractionFinished OnInteractionFinished;
};


UCLASS()
class MYQUESTMODULE_API AInteractableActor : public AActor
{
	GENERATED_BODY()
	
	UFUNCTION(BlueprintCallable)
	void OnInteractionFinished(AActor* ActorInteractedWithObject)
	{
		if (IInteractableObject* InteractableObject = Cast<IInteractableObject>(this))
		{
			InteractableObject->NotifyInteractionFinished(this, ActorInteractedWithObject);
		}
	}
};