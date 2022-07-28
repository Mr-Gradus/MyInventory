#include "Objective.h"

#include "CollectedActor.h"
#include "InteractableObject.h"
#include "KilledActor.h"
#include "LocationMarker.h"


UInteractionObjective::UInteractionObjective()
{
	Type = EObjectiveType::Interact;
}

void UInteractionObjective::ActivateObjective(AActor * Character)
{
	if (IInteractableObject * InteractableTarget = Cast<IInteractableObject>(Target))
	{
		InteractableTarget->OnInteractionFinished.AddLambda([this, Character](AActor* InteractableObject, const AActor* ActorInteractedWithObject)
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
		LocMarker->OnLocationReached.AddLambda([this, Character](AActor* LocationMarker, const AActor* OverlappedActor)
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


UCollectedObjective::UCollectedObjective()
{
	Type = EObjectiveType::Collect;
}

void UCollectedObjective::ActivateObjective(AActor* Character)
{
	if (ICollectedActor* Collected = Cast<ICollectedActor>(CollectedObject))
	{
		Collected->OnCollected.AddLambda([this, Character](AActor* CollectibleActor, AActor* OverlappedActor)
		{
			if (bCanBeCompleted && Character == OverlappedActor)
			{
				CollectedObject->SetActorHiddenInGame(true);

				bIsCompleted = true;
				
				if (OnObjectiveCompleted.IsBound())
				{
				   OnObjectiveCompleted.Broadcast(this);
				}
			}
		});
	}
}


UKilledObjective::UKilledObjective()
{
	Type = EObjectiveType::Kill;
}

void UKilledObjective::ActivateObjective(AActor* Character)
{
	if (IKilledActor* Killed = Cast<IKilledActor>(KilledObject))
	{
		Killed->OnKilled.AddLambda([this, Character](AActor* KilledActor, AActor* Killer)
		{
			if (bCanBeCompleted && Character == Killer)
			{
				KilledObject->Destroy();

				bIsCompleted = true;
				
				if (OnObjectiveCompleted.IsBound())
				{
				   OnObjectiveCompleted.Broadcast(this);
				}
			}
		});
	}
}