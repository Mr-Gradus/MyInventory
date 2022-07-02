#include "InventoryWidget.h"
#include <Components/UniformGridPanel.h>

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UInventoryWidget::Init(int32 ItemsNum)
{
	if (ItemCellsGrid)
	{
		ItemCellsGrid->ClearChildren();
		for(int32 i = 0; i < ItemsNum; i++)
		{
			UInventoryCellWidget* Widget = CreateCellWidget();
			Widget->IndexInInventory = i;
			ItemCellsGrid->AddChildToUniformGrid(Widget, i / ItemsInRow, i % ItemsInRow);
		}
	}
}

UInventoryCellWidget* UInventoryWidget::CreateCellWidget()
{
	if (CellWidgetClass)
	{
		UInventoryCellWidget* CellWidget = CreateWidget<UInventoryCellWidget>(this, CellWidgetClass);
		CellWidgets.Add(CellWidget);
		CellWidget->OnItemDrop.AddUObject(this,	&UInventoryWidget::OnItemDropped);

		return CellWidget;
	}
	return nullptr;
}

void UInventoryWidget::OnItemDropped(UInventoryCellWidget* DraggedFrom, UInventoryCellWidget* DroppedTo) const
{
	if (OnItemDrop.IsBound())
	{
		OnItemDrop.Broadcast(DraggedFrom, DroppedTo);
	}
}

bool UInventoryWidget::AddItem(const FInventorySlotInfo & Item, const FInventoryItemInfo& ItemInfo, int32 SlotPosition)
{
	if (ItemInfo.Type == EItemType::IT_Currency)
	{
		if (GoldCell)
		{
			return GoldCell->AddItem(Item, ItemInfo);
		}
		return false;
	}

	if (ItemCellsGrid)
	{
		UInventoryCellWidget* WidgetToAddItem = nullptr;
		UInventoryCellWidget** WidgetToAddItemPtr = CellWidgets.FindByPredicate([SlotPosition](UInventoryCellWidget* Widget)
		{
		return Widget && Widget->IndexInInventory == SlotPosition;
		});

		if (WidgetToAddItemPtr)
		{
			WidgetToAddItem = *WidgetToAddItemPtr;
		}
	else
	{
		for (UInventoryCellWidget* CellWidget : CellWidgets)
		{
			if (!CellWidget->HasItem())
			{
				WidgetToAddItem = CellWidget;
				break;
			}
		}
	}

		if (WidgetToAddItem)
		{
			return WidgetToAddItem->AddItem(Item, ItemInfo);
		}
	}
	return false;
}

void UInventoryWidget::TypeFilter(const TEnumAsByte<EItemType> Type)
{
	if (!ItemCellsGrid) return;

	for (UInventoryCellWidget* Widget : CellWidgets)
	{
		if (Widget->HasItem()) continue;

		const EItemType SlotType = Widget->GetItem().Type;
		Widget->SetSlotVisible(Type == SlotType || Type == EItemType::All);
	}
}