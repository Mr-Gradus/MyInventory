#include "InventoryManagerComponent.h"
#include "InventoryWidget.h"
#include <Blueprint/DragDropOperation.h>


UInventoryManagerComponent::UInventoryManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UInventoryManagerComponent::OnItemDropped(UInventoryCellWidget* DraggedFrom, UInventoryCellWidget* DraggedTo)
{
/*
	if(IsValid(DraggedFrom) || IsValid(DraggedTo))
	{
		const FInventorySlotInfo FromCell = DraggedFrom->GetItem();
		const FInventorySlotInfo ToCell = DraggedTo->GetItem();

		const FInventoryItemInfo* FromData = GetItemData(FromCell.ItemID);
		const FInventoryItemInfo* ToData = GetItemData(ToCell.ItemID);

		DraggedFrom->Clear();
		if (ToData)
		{
			DraggedFrom->AddItem(ToCell, *ToData);
		}
		
		DraggedTo->Clear();
		DraggedTo->AddItem(FromCell, *FromData);
	}
*/
/// Драг дроп для системы двух инвентарей не работает у меня


	if (DraggedFrom == nullptr || DraggedTo == nullptr)
	{
		return;
	}

	UInventoryComponent* FromInventory = DraggedFrom->ParentInventoryWidget->RepresentedInventory;
	UInventoryComponent* ToInventory = DraggedTo->ParentInventoryWidget->RepresentedInventory;

	if (FromInventory == nullptr || ToInventory == nullptr)
	{
		return;
	}

	LocalInventoryComponent->SetItem(DraggedFrom->IndexInInventory, DraggedTo->GetItem());
	LocalInventoryComponent->SetItem(DraggedTo->IndexInInventory, DraggedFrom->GetItem());

	FInventorySlotInfo FromSlotItem = DraggedFrom->GetItem();
	FInventorySlotInfo ToSlotItem = DraggedTo->GetItem();

	if (FromSlotItem.Amount <= 0)
	{
		return;
	}
	
	FInventoryItemInfo* FromInfoItem = GetItemData(FromSlotItem.ItemID);
	FInventoryItemInfo* ToInfoItem = GetItemData(ToSlotItem.ItemID);

	if (FromInfoItem == nullptr || (ToSlotItem.ItemID != NAME_None && ToInfoItem == nullptr))
	{
		return;
	}

	int32 MaxCount = ToInventory->GetMaxItemAmount(DraggedTo->IndexInInventory, *FromInfoItem);
	if (MaxCount == 0)
	{
		return;
	}
	else if (MaxCount < 0)
	{
		if (ToInventory != FromInventory && ToInfoItem != nullptr)
		{
			ToSlotItem.bUnequipProccess = true;
			ToSlotItem.bUnequipAndStack = true;

			FromSlotItem.Amount += ToSlotItem.Amount;
			FromSlotItem.ItemID = ToSlotItem.ItemID;
			FromInfoItem = ToInfoItem;

			ToSlotItem.Amount = 0;
		}
		else
		{
			MaxCount = 1;
		}
	}
	else if (MaxCount > 0)
	{
		int32 ItemsToAdd = FMath::Min(MaxCount, FromSlotItem.Amount);
		ToSlotItem.Amount = FromSlotItem.Amount - ItemsToAdd;
		ToSlotItem.ItemID = FromSlotItem.ItemID;
		ToInfoItem = FromInfoItem;

		FromSlotItem.Amount = ItemsToAdd;
	}

	FromInventory->SetItem(DraggedFrom->IndexInInventory, ToSlotItem);
	ToInventory->SetItem(DraggedTo->IndexInInventory, FromSlotItem);

	DraggedFrom->Clear();
	if (ToInfoItem)
	{
		DraggedFrom->AddItem(ToSlotItem, *ToInfoItem);
	}

	DraggedTo->Clear();
	DraggedTo->AddItem(FromSlotItem, *FromInfoItem);
}




void UInventoryManagerComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UInventoryManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UInventoryManagerComponent::Init(UInventoryComponent* InInventoryComponent)
{
	LocalInventoryComponent = InInventoryComponent;
	if (IsValid(LocalInventoryComponent) && IsValid(InventoryData))
	{
		ensure(InventoryWidgetClass);

		InventoryWidget = CreateWidget<UInventoryWidget>(GetWorld(),	InventoryWidgetClass);

		InventoryWidget->OnItemDrop.AddUObject(this, &UInventoryManagerComponent::OnItemDropped);

		InventoryWidget->RepresentedInventory = LocalInventoryComponent;
		
		InventoryWidget->AddToViewport();

		InventoryWidget->Init(FMath::Max(LocalInventoryComponent->GetItemsNum(), MinInventorySize));

		if (LocalInventoryComponent->InventoryClass)
		{
			LoadInventory(LocalInventoryComponent->InventoryClass);
		}
	}
}

void UInventoryManagerComponent::InitEquipment(UInventoryComponent* InInventoryComponent)
{
	ensure(EquipInventoryWidgetClass);

	EquipInventoryWidget = CreateWidget<UInventoryWidget>(GetWorld(), EquipInventoryWidgetClass);

	EquipInventoryWidget->OnItemDrop.AddUObject(this, &UInventoryManagerComponent::OnItemDropped);

	EquipInventoryWidget->RepresentedInventory = InInventoryComponent;

	EquipInventoryWidget->AddToViewport();

	

}

FInventoryItemInfo * UInventoryManagerComponent::GetItemData(FName ItemID) const
{
	if (IsValid(InventoryData))
	{
		return InventoryData->FindRow<FInventoryItemInfo>(ItemID, "");
	}
	return nullptr;
}

void UInventoryManagerComponent::LoadInventory(UDataTable* Class)
{
	TArray<FInventorySlotInfo*> Slots;
	Class->GetAllRows<FInventorySlotInfo>("", Slots);
		for (auto i = 0; i < Slots.Num(); ++i)	
		{
			LocalInventoryComponent->SetItem(i, *Slots[i]);
				const FInventoryItemInfo* ItemData = GetItemData(Slots[i]->ItemID);
				if (ItemData)
				{
					ItemData->Icon.LoadSynchronous();
					InventoryWidget->AddItem(*Slots[i], *ItemData);
				}
		}
}
