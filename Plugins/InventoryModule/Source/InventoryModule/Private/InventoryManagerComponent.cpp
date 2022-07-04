#include "InventoryManagerComponent.h"
#include "InventoryWidget.h"
#include <Blueprint/DragDropOperation.h>


UInventoryManagerComponent::UInventoryManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UInventoryManagerComponent::OnItemDropped(UInventoryCellWidget* DraggedFrom, UInventoryCellWidget* DraggedTo)
{

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

/// Драг дроп для системы двух инвентарей не работает у меня




	/*
	if(DraggedFrom || DraggedTo)
	{
		return;	
	}

	UInventoryComponent* FromInventory = DraggedFrom->ParentInventoryWidget->RepresentedInventory;
	UInventoryComponent* ToInventory = DraggedTo->ParentInventoryWidget->RepresentedInventory;

	if (!FromInventory || !ToInventory)
	{
		return;
	}
	
	FInventorySlotInfo FromCell = DraggedFrom->GetItem();

	FInventorySlotInfo ToCell = DraggedTo->GetItem();

	if (FromCell.Amount < 1)
	{
		return;
	}

	const FInventoryItemInfo* FromData = GetItemData(FromCell.ItemID);

	const FInventoryItemInfo* ToData = GetItemData(ToCell.ItemID);

	

	if (DraggedTo->IsEmpty())
	{
		ToCell = FromCell;

		ToCell.Amount = ToInventory->GetMaxItemAmount(DraggedTo->IndexInInventory, *FromData);
	}

	if (ToCell.Amount == 0)
	{
		return;
	}

	if (ToCell.Amount == -1)
	{
		ToCell.Amount = FromCell.Amount;
	}

	FromCell.Amount -= ToCell.Amount;
	

	DraggedFrom->Clear();

	if (FromCell.Amount)
	{
		DraggedFrom->AddItem(ToCell, *ToData);
		FromInventory->SetItem(DraggedFrom->IndexInInventory, FromCell);
	}
	else
	{
		FromInventory->ClearItem(DraggedFrom->IndexInInventory);
	}
		
		DraggedTo->Clear();
		DraggedTo->AddItem(FromCell, *FromData);
		ToInventory->SetItem(DraggedTo->IndexInInventory, ToCell);
*/

	////////////////////////////////
	/*

	if (FromData == nullptr || (ToCell.ItemID != NAME_None && ToData == nullptr))
	{
		return;
	}
	const int32 MaxCount = ToInventory->GetMaxItemAmount(DraggedTo->IndexInInventory, *FromData);
	if (MaxCount == 0)
	{
		return;
	}
	else if (MaxCount > 0)
	{
		const int ItemsToAdd = FMath::Min(MaxCount, FromCell.Amount);
		ToCell.Amount = FromCell.Amount - ItemsToAdd;
		ToCell.ItemID = FromCell.ItemID;
		ToData = FromData;

		FromCell.Amount = ItemsToAdd;
	}
	else if (FromCell.ItemID == ToCell.ItemID)
	{
		FromCell.Amount += ToCell.Amount;
		ToCell.Amount = 0;
	}

	FromInventory->SetItem(DraggedFrom->IndexInInventory, ToCell);
	ToInventory->SetItem(DraggedTo->IndexInInventory, FromCell);
	

	if (!FromCell || !ToCell)
	{
		return;
	}
	UInventoryComponent * FromInventory =
	FromCell->ParentInventoryWidget->RepresentedInventory;
	UInventoryComponent * ToInventory =
	ToCell->ParentInventoryWidget->RepresentedInventory;
	if (!FromInventory || !ToInventory)
	{
		return;
	}
	// split item amount between two inventories

	auto FromSlot{ FromCell->GetItem() };
	auto ToSlot{ ToCell->GetItem() };

	if (FromSlot.Amount < 1)
	{
		return;
	}

	auto FromInfo{ GetItemData(FromSlot.ItemID) };
	auto ToInfo{ GetItemData(ToSlot.ItemID) };





	FInventorySlotInfo ItemToDrop = ToCell->GetItem();
	ItemToDrop.Amount = ToInventory->GetMaxItemAmount(ToCell->IndexInInventory, *FromInfo);
	if (ItemToDrop.Amount == 0)
	{
		return;
	}
	if (ItemToDrop.Amount == -1)
	{
		ItemToDrop.Amount = ToSlot.Amount;
	}
	ToSlot.Amount -= ItemToDrop.Amount;
	FromCell->Clear();
	FromCell->AddItem(ToSlot, *ToInfo);
	ToCell->Clear();
	ToCell->AddItem(FromSlot, *FromInfo);
	FromInventory->SetItem(FromCell->IndexInInventory, FromSlot);
	ToInventory->SetItem(ToCell->IndexInInventory, ItemToDrop);
*/
	
/*
	if (!DraggedFrom || !DraggedTo)
	{
		return;
	}

	UInventoryComponent* FromInventory = DraggedFrom->ParentInventoryWidget->RepresentedInventory;
	UInventoryComponent* ToInventory = DraggedTo->ParentInventoryWidget->RepresentedInventory;

	if (!FromInventory || !ToInventory)
	{
		return;
	}

	FInventorySlotInfo FromSlot = DraggedFrom->GetItem();
	FInventorySlotInfo ToSlot = DraggedTo->GetItem();

	if (FromSlot.Amount < 1)
	{
		return;
	}

	const FInventoryItemInfo* FromInfo = GetItemData(FromSlot.ItemID);
	const FInventoryItemInfo* ToInfo = GetItemData(ToSlot.ItemID);

	if (FromInfo == nullptr || (ToSlot.ItemID != NAME_None && ToInfo == nullptr))
	{
		return;
	}

	const int32 MaxCount = ToInventory->GetMaxItemAmount(DraggedTo->IndexInInventory, *FromInfo);
	if (MaxCount == 0)
	{
		return;
	}
	else if (MaxCount > 0)
	{
		const int ItemsToAdd = FMath::Min(MaxCount, FromSlot.Amount);
		ToSlot.Amount = FromSlot.Amount - ItemsToAdd;
		ToSlot.ItemID = FromSlot.ItemID;

		ToInfo = FromInfo;

		FromSlot.Amount = ItemsToAdd;
	}
	else if (FromSlot.ItemID == ToSlot.ItemID)
	{
		FromSlot.Amount += ToSlot.Amount;
		ToSlot.Amount = 0;
	}

	FromInventory->SetItem(DraggedFrom->IndexInInventory, ToSlot);
	ToInventory->SetItem(DraggedTo->IndexInInventory, FromSlot);

	DraggedFrom->Clear();

	if (ToInfo)
	{
		DraggedFrom->AddItem(ToSlot, *ToInfo);
	}

	DraggedTo->Clear();
	DraggedTo->AddItem(FromSlot, *FromInfo);
	*/
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
