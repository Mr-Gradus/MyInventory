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
	virtual void CollectedObjective(AActor* CollectibleActor, AActor* OverlappedActor);

	FOnCollected FOnCollected;
};
