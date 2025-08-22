#include "Demo/Item/InventoryComponent.h"
#include "string"
#include "Demo/Item/PickupableItem.h"



UInventoryComponent::UInventoryComponent()
{
	
	PrimaryComponentTick.bCanEverTick = true;


}





void UInventoryComponent::AddItem(FInventoryItemData& Item)
{
	Inventory.Add(Item);
	UE_LOG(LogTemp, Warning, TEXT("ItemAddToInvenory"));


}


void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	
	
}



void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
}

