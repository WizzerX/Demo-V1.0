// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Demo/Item/PickupableItem.h"
#include "InventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSlotWidgetDelegate, int32, UI_Index, const FInventoryItemData&, Data);




UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEMO_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TArray<FInventoryItemData>Inventory;
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TArray<FInventoryItemData>slot;
		
	
	bool bItemFound = false;

protected:
	int32 Index = 0;
	

	virtual void BeginPlay() override;

public:	
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction*
		ThisTickFunction) override;
	FInventoryItemData GetItemAt( const int32 index);

	const int32 GetIndex() { return  Index; }
	
	UInventoryComponent();

	void AddItem( const FInventoryItemData& Item);

	void RemoveItem(const FInventoryItemData& Item);
	
	UPROPERTY(BlueprintAssignable)
	FSlotWidgetDelegate SlotWidgetDelegate;

	UFUNCTION()
	void HandlySlotUI(int32 UI_Index, const FInventoryItemData& Data);


	AMainCharacter* CharacterRef;

	int32 NewIndex;

private:
	int SlotLeft = 4;



};
