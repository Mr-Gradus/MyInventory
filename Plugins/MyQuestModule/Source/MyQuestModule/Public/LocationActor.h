#pragma once

#include "CoreMinimal.h"
#include "LocationMarker.h"
#include "GameFramework/Actor.h"
#include "LocationActor.generated.h"

UCLASS()
class MYQUESTMODULE_API ALocationActor : public AActor, public ILocationMarker
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable)
	void OnOverlappedByActor(AActor* OverlappingActor);	
};
