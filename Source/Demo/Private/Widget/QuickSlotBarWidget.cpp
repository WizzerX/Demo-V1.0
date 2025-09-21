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
#include "Components/Image.h"
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
			this, &UQuickSlotBarWidget::UpdateUIAt);
		
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
		UE_LOG(LogTemp, Warning, TEXT("INDEX UPDATE UI:%d"), index);
		
		if (Data.Quantity <= 0)
		{
		SlotBar[index]->QuantityText->SetText(FText::AsNumber(0));
		SlotBar[index]->ItemIcon->SetBrushFromTexture(nullptr);
		SlotBar[index]->ItemIcon->SetVisibility(ESlateVisibility::Hidden);
		SlotBar[index]->QuantityText->SetText(FText::GetEmpty());
		SlotBar[index]->QuantityText->SetVisibility(ESlateVisibility::Visible);
		UE_LOG(LogTemp, Warning, TEXT("Deleate the slot"), index);
		
			
		}


		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Slot Updated success !"), index);
			SlotBar[index]->ItemIcon->SetBrushFromTexture(Data.Icon);
			SlotBar[index]->ItemIcon->SetVisibility(ESlateVisibility::Visible);
			SlotBar[index]->QuantityText->SetText(FText::AsNumber(Data.Quantity));
			SlotBar[index]->QuantityText->SetVisibility(ESlateVisibility::Visible);
		}
	}


	
}


void UQuickSlotBarWidget::ChangeScore(int32 score)
{


	UE_LOG(LogTemp,Error, TEXT("INDEX UPDATE UI:%d"),score);

}
