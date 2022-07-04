#include "EquipInventoryComponent.h"

UEquipInventoryComponent::UEquipInventoryComponent()
{
	EquipSlots.Add(0, EEquipSlot::ES_Head);
	EquipSlots.Add(1, EEquipSlot::ES_Body);
	EquipSlots.Add(2, EEquipSlot::ES_RightHand);
	EquipSlots.Add(3, EEquipSlot::ES_LeftHand);
	EquipSlots.Add(4, EEquipSlot::ES_Finger);
	EquipSlots.Add(5, EEquipSlot::ES_Slot1);
	EquipSlots.Add(6, EEquipSlot::ES_Slot2);
}

int32 UEquipInventoryComponent::GetMaxItemAmount(int32 SlotIndex, const FInventoryItemInfo& Item)
{
	const FInventorySlotInfo* InfoPtr = Items.Find(SlotIndex);
	if (InfoPtr && InfoPtr->ItemID != NAME_None || Item.Type != EItemType::IT_Equipment || !EquipSlots.Contains(SlotIndex) || EquipSlots.FindChecked(SlotIndex) != Item.EquipSlot)
	{
		return 0;
	}

	return 1;
}

void UEquipInventoryComponent::SetItem(int32 SlotIndex, const FInventorySlotInfo& Item)
{
	FInventorySlotInfo * EquippedItem = GetItem(SlotIndex);

	EEquipSlot EquipSlot = EquipSlots.Contains(SlotIndex) ? EquipSlots.FindChecked(SlotIndex) : EEquipSlot::ES_None;

	if (EquippedItem && MyPlayer)
	{
		MyPlayer->UnequipItem(EquipSlot, EquippedItem->ItemID);
	}

	Super::SetItem(SlotIndex, Item);

	if (MyPlayer)
	{
		MyPlayer->EquipItem(EquipSlot, Item.ItemID);
	}
}