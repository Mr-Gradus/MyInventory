#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "KilledActor.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnKilled, AActor* /*Destroyed Pawn*/, AActor* /*Killer*/)

UINTERFACE(MinimalAPI)
class UKilledActor : public UInterface
{
	GENERATED_BODY()
};

class MYQUESTMODULE_API IKilledActor
{
	GENERATED_BODY()

public:

	virtual void KilledTarget(AActor* Target, AActor* Killer)
	{
		if (OnKilled.IsBound())
		{
			OnKilled.Broadcast(Target, Killer);  
		}
	}

	FOnKilled OnKilled;
};

UCLASS()
class MYQUESTMODULE_API AKilledActorObject : public AActor, public IKilledActor
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable)
		void OnProjectileCollision(AActor* Projectile)			
	{
		KilledTarget(this, Projectile->GetOwner());
	}
};