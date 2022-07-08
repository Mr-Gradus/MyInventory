// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EquipInventoryComponent.h"
#include "InteractionComponent.h"
#include "InventoryComponent.h"
#include "InventoryCellWidget.h"
#include "GameFramework/Character.h"
#include "InventoryManagerComponent.h"
#include "QuestListComponent.h"
#include "Engine/DataTable.h"
#include "MyInventoryCharacter.generated.h"

class UWidgetComponent;
class UInventoryComponent;
class UInventoryManagerComponent;

UCLASS(Blueprintable)
class AMyInventoryCharacter : public ACharacter, public IInventoryCharacterInterface
{
	GENERATED_BODY()

public:
	AMyInventoryCharacter();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void ChangeClassCharacter(UDataTable* ClassDataTable) const;
	void EquipItem(EEquipSlot Slot, FName ItemID);
	void UnequipItem(EEquipSlot Slot, FName ItemID);
	UStaticMeshComponent* GetEquipComponent(EEquipSlot Slot) const;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns CursorToWorld subobject **/
	FORCEINLINE class UDecalComponent* GetCursorToWorld() { return CursorToWorld; }

	UPROPERTY(EditDefaultsOnly)
	UInventoryComponent* InventoryComponent;

	UPROPERTY(EditDefaultsOnly)
	UInventoryManagerComponent* InventoryManagerComponent;

	UPROPERTY(EditDefaultsOnly)
	UEquipInventoryComponent* EquipmentInventoryComponent;

	UPROPERTY(EditDefaultsOnly)
	UInteractionComponent* InteractionComponent;

	UPROPERTY(EditDefaultsOnly)
	UQuestListComponent* QuestListComponent;
private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** A decal that projects to the cursor location. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UDecalComponent* CursorToWorld;
};

