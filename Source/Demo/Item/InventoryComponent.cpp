#include "Demo/Item/InventoryComponent.h"
#include "string"
#include "Demo/Item/PickupableItem.h"



UInventoryComponent::UInventoryComponent()
{
	
	PrimaryComponentTick.bCanEverTick = true;
	//Inventory.SetNum(4);

	






	
}








void UInventoryComponent::AddItem(const FInventoryItemData& Item)
{
	bItemFound = false;

	for (int i = 0; i < slot.Num(); i++)
	{
		if (Item.ItemName == slot[i].ItemName)
		{
			bItemFound = true;
			if (slot[i].Quantity< 5)
			{
				slot[i].Quantity +=Item.Quantity;
				SlotWidgetDelegate.Broadcast(i, slot[i]);
		
				UE_LOG(LogTemp, Error, TEXT("Quantity Item Added!"));
			}
			else
			{
				Index++;
				slot.Add(Item);
				SlotWidgetDelegate.Broadcast(i, slot[i]);
				UE_LOG(LogTemp, Error, TEXT("Slot Item Added!"));
				
			}
			break;

		}
	
	}
	if (!bItemFound)
	{
		Index++;
		slot.Add(Item);
		SlotWidgetDelegate.Broadcast(Index, slot[Index]);
		UE_LOG(LogTemp, Error, TEXT("Slot Item Added!"));
	}


}

void UInventoryComponent::RemoveItem(const FInventoryItemData& Item)
{
	for (int i = 0; i < slot.Num();i++)
	{
		if (slot[i].ItemName == Item.ItemName)
		{
			Inventory[i].Quantity--;
			if (Inventory[i].Quantity <= 0)
			{
				slot[i] = FInventoryItemData();
				Index--;
			}
			break;
		}
		
	}

}

void UInventoryComponent::HandlySlotUI(int32 UI_Index,const FInventoryItemData& Data)
{

	UE_LOG(LogTemp, Error, TEXT("Handly slot UI"));




}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	SlotWidgetDelegate.AddDynamic(this, &UInventoryComponent::HandlySlotUI);
	
}



void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
}

FInventoryItemData UInventoryComponent::GetItemAt( const int32 index)
{
	if (slot.IsValidIndex(index))
	{
		return  slot[index];
	}
	else
	{
			  // Return a default item instead of empty reference
			  FInventoryItemData DefaultItem;
			  DefaultItem.ItemName = FName("Empty");
			  DefaultItem.Quantity = 0;
			  return DefaultItem;
			  
	}

}


