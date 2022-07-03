#include "InventoryManagerComponent.h"
#include "InventoryWidget.h"
#include <Blueprint/DragDropOperation.h>


UInventoryManagerComponent::UInventoryManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UInventoryManagerComponent::OnItemDropped(UInventoryCellWidget* DraggedFrom, UInventoryCellWidget* DraggedTo) const
{
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
