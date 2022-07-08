#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "LocationMarker.generated.h"


DECLARE_MULTICAST_DELEGATE_TwoParams(FOnLocationReached, AActor* /*LocationMarker*/, AActor* /*OverlappedActor*/);

UINTERFACE(MinimalAPI)
class ULocationMarker : public UInterface
{
	GENERATED_BODY()
};


class MYQUESTMODULE_API ILocationMarker
{
	GENERATED_BODY()
public:

	virtual void NotifyOverlapWithActor(AActor* LocationMarker, AActor* OverlappedActor)
	{
		if (OnLocationReached.IsBound())
		{
			OnLocationReached.Broadcast(LocationMarker, OverlappedActor);
		}
	}
	FOnLocationReached OnLocationReached;
};

UCLASS()
class MYQUESTMODULE_API ALocationMarkerActor : public AActor, public ILocationMarker
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void OnOverlapedByActor(AActor* OverlappingActor)
	{
		NotifyOverlapWithActor(this, OverlappingActor);
	}
};



