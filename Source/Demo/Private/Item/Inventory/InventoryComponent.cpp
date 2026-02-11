#include "Item/Inventory/InventoryComponent.h"
#include "string"
#include "Item/Interactable/PickupableItem.h"
#include "character/MainCharacter.h"


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
			CharacterRef->CurrentItem = nullptr;
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
					slot[j].IdCode = FGuid::NewGuid();
					SlotWidgetDelegate.Broadcast(j, slot[j]);
					CharacterRef->CurrentItem->Destroy();
					UE_LOG(LogTemp, Error, TEXT("Reused empty slot: %d"), j);
					return;
				}
			}
				if (slot.Num()<6)
				{
					
					
					int32 index=slot.Add(Item);
					slot[index].IdCode = FGuid::NewGuid();
					SlotWidgetDelegate.Broadcast(index, slot[index]);
					CharacterRef->CurrentItem->Destroy();
					UE_LOG(LogTemp, Error, TEXT("NEW ITEM ADDDED !"));
				}
			
		}

	
	



	
}
int32 UInventoryComponent::FindIndexById(FGuid ID)
{
	for (int32 index = 0; index < slot.Num(); index++)
	{
		if (slot[index].IdCode == ID)
		{
			
			UE_LOG(LogTemp, Error, TEXT("Finded ID IS: %s"),*slot[index].IdCode.ToString());
			return index;
			
			
		}

	}
	

	UE_LOG(LogTemp, Error, TEXT("FindIndexById :-1"));
	return -1;
}

void UInventoryComponent::RemoveItemAt(int32 RemovingIndex)
{

	if (!slot.IsValidIndex(RemovingIndex))
	{
	
		return;
	}

	slot[RemovingIndex].Quantity--;

	SlotWidgetDelegate.Broadcast(RemovingIndex, slot[RemovingIndex]);

	if (slot[RemovingIndex].Quantity <= 0)
	{
		//slot[RemovingIndex].IdCode = FGuid::NewGuid();
		slot[RemovingIndex] = FInventoryItemData();
		SlotWidgetDelegate.Broadcast(RemovingIndex, FInventoryItemData());
	}
	

}

void UInventoryComponent::RemoveItem(const FInventoryItemData& Item)
{
	for (int index = 0; index < slot.Num(); index++)
	{

		if (slot[index].IdCode == Item.IdCode)
		{
			
			slot[index].Quantity--;

			SlotWidgetDelegate.Broadcast(index, slot[index]);
			if (slot[index].Quantity <= 0)
			{
				slot[index] = FInventoryItemData();
				SlotWidgetDelegate.Broadcast(index, slot[index]);
				return;

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

bool UInventoryComponent::IsValidIndex(const int32 index) const
{

	return slot.IsValidIndex(index);


	
}


