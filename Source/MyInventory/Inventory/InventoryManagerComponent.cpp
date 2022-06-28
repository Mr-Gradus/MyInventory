#include "InventoryManagerComponent.h"
#include "InventoryWidget.h"
#include "Blueprint/DragDropOperation.h"

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
	if (IsValid(LocalInventoryComponent) && IsValid(InventoryData) && IsValid((InventoryID)))
	{
		ensure(InventoryWidgetClass);

		InventoryWidget = CreateWidget<UInventoryWidget>(GetWorld(),	InventoryWidgetClass);

		InventoryWidget->OnItemDrop.AddUObject(this, &UInventoryManagerComponent::OnItemDropped);

		InventoryWidget->AddToViewport();

		InventoryWidget->Init(FMath::Max(LocalInventoryComponent->GetItemsNum(), MinInventorySize));

		TArray<FInventorySlotInfo*> Slots;
		InventoryID->GetAllRows<FInventorySlotInfo>("", Slots);
		for (auto i = 0; i < Slots.Num(); ++i)
		{
			LocalInventoryComponent->SetItem(i, *Slots[i]);
					
		}	

		for (auto&  Item: LocalInventoryComponent->GetItems()) 
		{
			
			FInventoryItemInfo* ItemData = GetItemData(Item.Value.ItemID);
			if (ItemData)
			{
				ItemData->Icon.LoadSynchronous();
				InventoryWidget->AddItem(Item.Value, *ItemData, Item.Key);
			}
		}

	}
}
// 
/*
*TArray<FInventorySlotInfo*> Slots;
	InventoryList->GetAllRows<FInventorySlotInfo>("", Slots);

	for (auto i = 0; i < Slots.Num(); ++i)
	{
		SetItem(i, *Slots[i]);
	}
 */
FInventoryItemInfo * UInventoryManagerComponent::GetItemData(FName ItemID) const
{
	if (IsValid(InventoryData))
	{
		return InventoryData->FindRow<FInventoryItemInfo>(ItemID, "");
	}
	return nullptr;
}
/*
void UInventoryManagerComponent::LoadInventory()
{
	TArray<FInventorySlotInfo*> Slots;
	InventoryID->GetAllRows<FInventorySlotInfo>("", Slots);

	for (auto i = 0; i < Slots.Num(); ++i)
	{
		SetItem(i, *Slots[i]);
	}
}
*/