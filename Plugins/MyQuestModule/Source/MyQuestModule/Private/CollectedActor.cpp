#include "CollectedActor.h"

void ICollectedActor::CollectedObjective(AActor* CollectibleActor, AActor* OverlappedActor)
{
	if(FOnCollected.IsBound())
	{
		FOnCollected.Broadcast(CollectibleActor, OverlappedActor);
	}
}
