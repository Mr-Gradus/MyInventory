#pragma once

#include <CoreMinimal.h>
#include "InventoryItem.h"
#include <Blueprint/UserWidget.h>
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "InventoryCellWidget.generated.h"

class UInventoryCellWidget;
class UImage;
class UTextBlock;

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnItemDrop, UInventoryCellWidget* DraggedFrom, UInventoryCellWidget* DroppedTo);

UCLASS()
class INVENTORYMODULE_API UInventoryCellWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	bool AddItem(const FInventorySlotInfo& Item, const FInventoryItemInfo& ItemInfo);

	void Clear();

	UFUNCTION(BlueprintCallable)
	const FInventorySlotInfo& GetItem() const;

	bool HasItem() const;

	int32 IndexInInventory;

	FOnItemDrop OnItemDrop;

	UFUNCTION(BlueprintCallable)
	void SetSlotVisible(bool Value);
protected:
	bool bHasItem;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	UPROPERTY(EditAnywhere)
	bool bIsDraggable = true;

	UPROPERTY(meta = (BindWidgetOptional))
	UImage* ItemImage;

	UPROPERTY(meta = (BindWidgetOptional))
	UTextBlock* CountText;

	UPROPERTY()
	FInventorySlotInfo StoredItem;
};
