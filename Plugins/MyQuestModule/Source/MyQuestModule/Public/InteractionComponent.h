#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "InteractionComponent.generated.h"

class UUserWidget;

UCLASS(ClassGroup = "Collision", meta = (DisplayName = "Interaction Collision", BlueprintSpawnableComponent))
class MYQUESTMODULE_API UInteractionComponent : public UBoxComponent
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void Interact();
protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> InteractMessageClass;

	UPROPERTY()
	UUserWidget* InteractMessage;

	UPROPERTY()
	AActor* ActorToInteract;

	UFUNCTION()
	void OnInteractionCompBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void OnInteractionCompEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
