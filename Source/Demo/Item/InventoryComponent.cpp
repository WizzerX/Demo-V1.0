#include "Demo/Item/InventoryComponent.h"
#include "string"
#include "Demo/Item/PickupableItem.h"
#include "array"




UInventoryComponent::UInventoryComponent()
{
	
	PrimaryComponentTick.bCanEverTick = true;
	//Inventory.SetNum(4);



	
}








void UInventoryComponent::AddItem(const FInventoryItemData& Item)
{
	bItemFound = false;

	for (int i = 0; i < Inventory.Num(); i++)
	{
		if (Item.ItemName == Inventory[i].ItemName)
		{
			bItemFound = true;
			if (Inventory[i].Quantity< 5)
			{
				Inventory[i].Quantity++;
				UE_LOG(LogTemp, Error, TEXT("Quantity Item Added!"));
			}
			else
			{
				Inventory.Add(Item);
				UE_LOG(LogTemp, Error, TEXT("Inventory Item Added!"));
			}
			break;

		}
	
	}
	if (!bItemFound)
	{
		Inventory.Add(Item);
		UE_LOG(LogTemp, Error, TEXT("Inventory Item Added!"));

	}


}

void UInventoryComponent::RemoveItem(const FInventoryItemData& Item)
{
	for (int i = 0; i < Inventory.Num();i++)
	{
		if (Inventory[i].ItemName == Item.ItemName)
		{
			Inventory[i].Quantity--;
			if (Inventory[i].Quantity <= 0)
			{
				Inventory[i] = FInventoryItemData();
				
			}
			break;
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
		return  Inventory[index];
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

