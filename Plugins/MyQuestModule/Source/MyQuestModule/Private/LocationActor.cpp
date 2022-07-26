#include "LocationActor.h"

void ALocationActor::OnOverlappedByActor(AActor* OverlappingActor)
{
	NotifyOverlapWithActor(this, OverlappingActor);
}