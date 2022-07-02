#pragma once

#include <CoreMinimal.h>
#include "InventoryCellWidget.h"
#include "InventoryComponent.h"
#include "InventoryItem.h"
#include <Components/ActorComponent.h>
#include "Engine/DataTable.h"
#include "InventoryManagerComponent.generated.h"

class UInventoryWidget;
struct FInventoryItemInfo;
class UInventoryComponent;
class UInventoryCellWidget;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INVENTORYMODULE_API UInventoryManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInventoryManagerComponent();

	void OnItemDropped(UInventoryCellWidget* DraggedFrom, UInventoryCellWidget* DraggedTo) const;
	
	void Init(UInventoryComponent* InInventoryComponent);

	FInventoryItemInfo* GetItemData(FName ItemID) const;

	UFUNCTION(BlueprintCallable)
	void LoadInventory(UDataTable* Class);

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	UInventoryComponent* LocalInventoryComponent;

	UPROPERTY(EditAnywhere)
	UDataTable* InventoryData;

	UPROPERTY()
    UInventoryWidget* InventoryWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UInventoryWidget> InventoryWidgetClass;

    UPROPERTY(EditAnywhere)
    int32 MinInventorySize = 20;


public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
