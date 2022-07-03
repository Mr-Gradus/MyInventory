#pragma once
#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InventoryItem.h"
#include "InventoryCharacterInterface.generated.h"

UINTERFACE(MinimalAPI)
class UInventoryCharacterInterface : public UInterface
{
	GENERATED_BODY()
};

class INVENTORYMODULE_API IInventoryCharacterInterface
{
	GENERATED_BODY()

public:
	virtual void EquipItem(EEquipSlot Slot, FName ItemID) {}

	virtual void UnequipItem(EEquipSlot Slot, FName ItemID) {}
};
