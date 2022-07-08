#include "Objective.h"
#include "InteractableObject.h"
#include "LocationMarker.h"


UInteractionObjective::UInteractionObjective()
{
	Type = EObjectiveType::Interact;
}

void UInteractionObjective::ActivateObjective(AActor * Character)
{
	if (IInteractableObject * InteractableTarget = Cast<IInteractableObject>(Target))
	{
		InteractableTarget->OnInteractionFinished.AddLambda([this, Character](
		AActor* InteractableObject, const AActor* ActorInteractedWithObject)
		{

			if (bCanBeCompleted && Character == ActorInteractedWithObject)
			{
				bIsCompleted = true;
				if (OnObjectiveCompleted.IsBound())
				{
					OnObjectiveCompleted.Broadcast(this);
				}
			}
		});
	}
}

ULocationObjective::ULocationObjective()
{
	Type = EObjectiveType::Location;
}

void ULocationObjective::ActivateObjective(AActor * Character)
{
	if (ILocationMarker * LocMarker = Cast<ILocationMarker>(Marker))
	{
		LocMarker->OnLocationReached.AddLambda([this, Character](
		AActor* LocationMarker, const AActor* OverlappedActor)
		{
			if (bCanBeCompleted && Character == OverlappedActor)
			{
				bIsCompleted = true;
				if (OnObjectiveCompleted.IsBound())
				{
					OnObjectiveCompleted.Broadcast(this);
				}
			}
		});
	}
}
