#include "KilledActor.h"

void IKilledActor::Killed(AActor* DestroyedPawn, AActor* Killer)
{
	if(FOnKilled.IsBound())
	{
		FOnKilled.Broadcast(DestroyedPawn, Killer);
	}
}