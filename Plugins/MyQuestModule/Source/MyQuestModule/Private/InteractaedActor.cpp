#include "InteractedActor.h"

void AInteractedActor::OnInteractionFinished(AActor* InteractInstigator)
{
	NotifyInteractionFinished(this, InteractInstigator);
}
