#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CollectedActor.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnCollected, AActor* /*CollectibleActor*/, AActor* /*OverlappedActor*/);

UINTERFACE(MinimalAPI)
class UCollectedActor : public UInterface
{
	GENERATED_BODY()
};

class MYQUESTMODULE_API ICollectedActor
{
	GENERATED_BODY()

public:
	void CatchUpEvent(AActor* Collectible, AActor* Collector)
	{
		if (OnCollected.IsBound())
		{
			OnCollected.Broadcast(Collectible, Collector);
		}
	}
	
	FOnCollected OnCollected;
};

UCLASS()
class MYQUESTMODULE_API ACollectibleActorObject : public AActor, public ICollectedActor
{
	GENERATED_BODY()
	
	UFUNCTION(BlueprintCallable)
	void ContactWithActor(AActor* OverlappingActor)
	{
		CatchUpEvent(this, OverlappingActor);
	}
};
