#pragma once

#include <CoreMinimal.h>
#include <Components/ActorComponent.h>
#include "InventoryItem.h"
#include "InventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INVENTORYMODULE_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInventoryComponent();
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<int32, FInventorySlotInfo> Items;

	FInventorySlotInfo * GetItem(int32 SlotIndex);

	
	
public:	

	UPROPERTY()
	UDataTable* InventoryClass;
	
	void SetItem(int32 SlotIndex, const FInventorySlotInfo& Item);

	void ClearItem(int32 SlotIndex);

	const TMap<int32, FInventorySlotInfo>& GetItems();

	int32 GetItemsNum() const;
};
