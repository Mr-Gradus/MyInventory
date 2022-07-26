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

	FOnKilled FOnKilled;

	virtual void Killed(AActor* DestroyedPawn, AActor* Killer);
};