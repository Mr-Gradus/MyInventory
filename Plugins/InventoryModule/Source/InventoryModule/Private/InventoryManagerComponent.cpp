#include "InventoryManagerComponent.h"
#include "InventoryWidget.h"
#include <Blueprint/DragDropOperation.h>


UInventoryManagerComponent::UInventoryManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UInventoryManagerComponent::OnItemDropped(UInventoryCellWidget* DraggedFrom, UInventoryCellWidget* DraggedTo) const
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

		InventoryWidget->AddToViewport();

		InventoryWidget->Init(FMath::Max(LocalInventoryComponent->GetItemsNum(), MinInventorySize));

		if (LocalInventoryComponent->InventoryClass)
		{
			LoadInventory(LocalInventoryComponent->InventoryClass);
		}
	}
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
