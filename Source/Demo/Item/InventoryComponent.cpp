#include "Demo/Item/InventoryComponent.h"
#include "string"
#include "Demo/Item/PickupableItem.h"



UInventoryComponent::UInventoryComponent()
{
	
	PrimaryComponentTick.bCanEverTick = true;


}








void UInventoryComponent::AddItem( const FInventoryItemData& Item)
{
	for (int i = 0; i < Inventory.Num(); i++)
	{
		if (Item.ItemName == Inventory[i].ItemName)
		{
			Inventory[i].Quantity += 1;

		}
		else
		{
			Inventory.Add(Item);
		}

	}



	Inventory.Add(Item);															
	UE_LOG(LogTemp, Warning, TEXT("ItemAddToInvenory"));						


}

void UInventoryComponent::RemoveItem(const FInventoryItemData& Item)
{
	for (int i = 0; i < Inventory.Num(); ++i)
	{
		if (Inventory[i].ItemName == Item.ItemName)
		{
			if (Inventory[i].Quantity == 0)
			{
				Inventory.RemoveAt(i);
				break;
			}

			Inventory[i].Quantity -= 1;
		}
	}






}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	
	
}



void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
}

FInventoryItemData UInventoryComponent::GetItemAt( const int32 index)
{
	if (Inventory.IsValidIndex(index))
	{
		return Inventory[index];
	}
	else
	{
		return FInventoryItemData();
	}

}

