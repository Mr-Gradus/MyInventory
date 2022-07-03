#pragma once

#include <CoreMinimal.h>
#include "InventoryCellWidget.h"
#include "InventoryComponent.h"
#include "InventoryItem.h"
#include "Blueprint/UserWidget.h"
//#include "Components/UniformGridPanel.h"
#include "InventoryWidget.generated.h"

class UUniformGridPanel;

UCLASS()
class INVENTORYMODULE_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;
	
	void Init(int32 ItemsNum);
	
	bool AddItem(const FInventorySlotInfo& Item, const FInventoryItemInfo& ItemInfo, int32 SlotPosition = -1);

	void InitCellWidget(UInventoryCellWidget* Widget);

	FOnItemDrop OnItemDrop;

	UPROPERTY()
	UInventoryComponent * RepresentedInventory;

protected:
	UPROPERTY(meta = (BindWidgetOptional))
	UUniformGridPanel* ItemCellsGrid;

	UPROPERTY(EditDefaultsOnly)
	int32 ItemsInRow = 3;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UInventoryCellWidget> CellWidgetClass;

	UPROPERTY(BlueprintReadWrite)
	TArray<UInventoryCellWidget*> CellWidgets;

	UPROPERTY(meta = (BindWidgetOptional))
	UInventoryCellWidget* GoldCell;

	UInventoryCellWidget* CreateCellWidget();


	void OnItemDropped(UInventoryCellWidget * DraggedFrom, UInventoryCellWidget * DroppedTo) const;

	UFUNCTION(BlueprintCallable)
	void TypeFilter(const TEnumAsByte<EItemType> Type);
};
