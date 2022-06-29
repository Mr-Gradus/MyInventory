#include "MyInventory/Inventory/InventoryCellWidget.h"
#include "InventoryDragDropOperation.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

bool UInventoryCellWidget::AddItem(const FInventorySlotInfo& Item, const FInventoryItemInfo& ItemInfo)
{
	if (bHasItem)
	{
		return false;
	}
	
	if (ItemImage)
	{
		ItemImage->SetBrushFromTexture(ItemInfo.Icon.Get());
		ItemImage->SetColorAndOpacity(FLinearColor(1.f, 1.f, 1.f));
	}
	
	if (CountText)
	{
		CountText->SetText(FText::FromString(FString::FromInt(Item.Amount)));
	}
	bHasItem = true;
	StoredItem = Item;
	return true;
}

void UInventoryCellWidget::Clear()
{
	if (ItemImage)
	{
		ItemImage->SetBrush(FSlateBrush());
		ItemImage->SetColorAndOpacity(FLinearColor(0.317708f, 0.259914f, 0.050768f, 1.f));
	}
	if (CountText)
	{
		CountText->SetText(FText::FromString("0"));

	}
	bHasItem = false;
	StoredItem = FInventorySlotInfo();
}

const FInventorySlotInfo& UInventoryCellWidget::GetItem() const
{
	return StoredItem;
}

bool UInventoryCellWidget::HasItem() const
{
	return bHasItem;
}

FReply UInventoryCellWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (bIsDraggable && bHasItem && InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this,EKeys::LeftMouseButton).NativeReply;
	}
	return FReply::Handled();
}

void UInventoryCellWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,	UDragDropOperation*& OutOperation)
{
	OutOperation = UWidgetBlueprintLibrary::CreateDragDropOperation(UInventoryDragDropOperation::StaticClass());
	UInventoryDragDropOperation* InventoryDragDropOperation = Cast<UInventoryDragDropOperation>(OutOperation);

	if (InventoryDragDropOperation)
    {
		InventoryDragDropOperation->SourceCell = this;
		InventoryDragDropOperation->DefaultDragVisual = this;
    }
    else
    {
    	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
	}	
}

bool UInventoryCellWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{

	UInventoryDragDropOperation* InventoryDragDropOperation = Cast<UInventoryDragDropOperation>(InOperation);

	if (InventoryDragDropOperation && InventoryDragDropOperation->SourceCell != this)
    {
		if (OnItemDrop.IsBound())
		{
			OnItemDrop.Broadcast(InventoryDragDropOperation->SourceCell, this);
		}
    }
	return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}

void UInventoryCellWidget::SetSlotVisible(const bool Value)
{
	if (ItemImage)
	{
		ItemImage->SetVisibility(Value ? ESlateVisibility::SelfHitTestInvisible: ESlateVisibility::Collapsed);
	}

	if (CountText)
	{
		CountText->SetVisibility(Value ? ESlateVisibility::SelfHitTestInvisible: ESlateVisibility::Collapsed);
	}
}