#pragma once

#include <CoreMinimal.h>

#include "InventoryComponent.h"
#include "InventoryItem.h"
#include "EquipInventoryComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class INVENTORYMODULE_API UEquipInventoryComponent : public UInventoryComponent
{
	GENERATED_BODY()

public:
	UEquipInventoryComponent();

	virtual int32 GetMaxItemAmount(int32 SlotIndex, const FInventoryItemInfo& Item) override;
	virtual void SetItem(int32 SlotIndex, const FInventorySlotInfo& Item) override;
	virtual void ClearItem(int32 SlotIndex) override;
protected:
	UPROPERTY(EditAnywhere)
	TMap<int32, EEquipSlot> EquipSlots;

};