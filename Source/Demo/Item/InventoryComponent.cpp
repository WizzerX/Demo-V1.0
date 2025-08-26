#include "Demo/Item/InventoryComponent.h"
#include "string"
#include "Demo/Item/PickupableItem.h"



UInventoryComponent::UInventoryComponent()
{
	
	PrimaryComponentTick.bCanEverTick = true;


}








void UInventoryComponent::AddItem( const FInventoryItemData& Item)
{
	Inventory.Add(Item);															
	UE_LOG(LogTemp, Warning, TEXT("ItemAddToInvenory"));						


}

void UInventoryComponent::RemoveItem(const FInventoryItemData& Item)
{
	for (int i = 0; i < Inventory.Num(); ++i)
	{
		if (Inventory[i].ItemName == Item.ItemName)
		{
			Inventory.RemoveAt(i);
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
		return Inventory[index];
	}
	else
	{
		return FInventoryItemData();
	}

}

