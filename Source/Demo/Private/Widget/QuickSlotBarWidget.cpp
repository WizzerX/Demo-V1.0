// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/QuickSlotBarWidget.h"
#include "Components/Widget.h"
#include "Widget/QuickSlotWidget.h"
#include "Components/UniformGridPanel.h" 
#include "Demo/Charcter/MainCharacter.h"
#include "Demo/Item/InventoryComponent.h"
#include "Components/TextBlock.h"
#include "Demo/Item/PickupableItem.h"
#include "Demo/Public/Widget/QuickSlotWidget.h"

void UQuickSlotBarWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SlotBar.Empty();

	for (size_t i = 0; i < 4; i++)
	{
		QuickSlotWidget = CreateWidget<UQuickSlotWidget>(this, QuickSlotClass);
		UE_LOG(LogTemp, Warning, TEXT("Bar Contructed!: %d"),i);
		
		SlotBar.Add(QuickSlotWidget);
		if (Grid)
		{
			Grid->AddChildToUniformGrid(QuickSlotWidget, 0, i);
		}


	}


	TestDelegate.AddDynamic(this, &UQuickSlotBarWidget::ChangeScore);
	CharacterRef = Cast<AMainCharacter>(GetOwningPlayerPawn());
	if (CharacterRef)
	{
		UE_LOG(LogTemp, Warning, TEXT("Delegate binding success"));
		CharacterRef->InventoryComponent->SlotWidgetDelegate.AddDynamic(
			this, &UQuickSlotBarWidget::UpdateUIAt
		);
		
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Delegate binding fAILED"));
	}


}

void UQuickSlotBarWidget::AddWidget()
{
	



}

void UQuickSlotBarWidget::UpdateUIAt(int32 index,const FInventoryItemData& Data)
{
	
	

	if (SlotBar.IsValidIndex(index))
	{
		SlotBar[index]->UpdateUI(Data.Icon,Data.Quantity);
		UE_LOG(LogTemp, Warning, TEXT("INDEX UPDATE UI:%d"), index);

	}


	
}


void UQuickSlotBarWidget::ChangeScore(int32 score)
{


	UE_LOG(LogTemp,Error, TEXT("INDEX UPDATE UI:%d"),score);

}
