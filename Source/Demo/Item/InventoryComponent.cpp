#include "Demo/Item/InventoryComponent.h"
#include "string"
#include "Demo/Item/PickupableItem.h"
#include "Demo/Charcter/MainCharacter.h"


UInventoryComponent::UInventoryComponent()
{
	
	PrimaryComponentTick.bCanEverTick = true;
	//Inventory.SetNum(4);

	CharacterRef = Cast<AMainCharacter>(this->GetOwner());
	if (CharacterRef)
	{
		UE_LOG(LogTemp, Warning, TEXT("Inventory cast scuess!"));
	}





	
}








void UInventoryComponent::AddItem(const FInventoryItemData& Item)
{
	bItemFound = false;

	for (int i = 0; i < slot.Num(); i++)
	{
		if (Item.ItemName == slot[i].ItemName && slot.IsValidIndex(i) && Item.stackable==true)
		{
			bItemFound = true;


			slot[i].Quantity += Item.Quantity;
			SlotWidgetDelegate.Broadcast(i, slot[i]);
			UE_LOG(LogTemp, Error, TEXT("Quantity Added to the slot:"));
			CharacterRef->CurrentItem->Destroy();
			return;


		}
	}
		// If not found, try to put in an empty slot
		if (!bItemFound)
		{
			for (int j = 0; j < slot.Num(); j++)
			{
				if (slot[j].ItemName.IsNone()) // empty slot
				{
					slot[j] = Item;
					SlotWidgetDelegate.Broadcast(j, slot[j]);
					CharacterRef->CurrentItem->Destroy();
					UE_LOG(LogTemp, Error, TEXT("Reused empty slot: %d"), j);
					return;
				}
			}
				if (slot.Num()<4)
				{
					int32 index=slot.Add(Item);
					SlotWidgetDelegate.Broadcast(index, slot[index]);
					CharacterRef->CurrentItem->Destroy();
					UE_LOG(LogTemp, Error, TEXT("NEW ITEM ADDDED !"));
				}
			
		}

	
	



	
}

void UInventoryComponent::RemoveItem(const FInventoryItemData& Item)
{
	for (int i = 0; i < slot.Num();i++)
	{
		if (slot[i].ItemName == Item.ItemName)
		{
			slot[i].Quantity--;
			
			SlotWidgetDelegate.Broadcast(i, slot[i]);
			if (slot[i].Quantity <= 0)
			{
				slot[i] = FInventoryItemData();
				SlotWidgetDelegate.Broadcast(i,slot[i]);
				
				break;
			}
			
		}
		
	}

}

void UInventoryComponent::HandlySlotUI(int32 UI_Index,const FInventoryItemData& Data)
{

	




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


