// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/QuickSlotWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/SizeBox.h"
#include "Item/Interactable/PickupableItem.h"
#include "character/MainCharacter.h"
#include "Item/Inventory/InventoryComponent.h"
#include "Item/Inventory/InventoryComponent.h"
#include "Components/Button.h"
#include "components/Border.h"


void UQuickSlotWidget::UpdateUI(UTexture2D* Icon, int32 Quantity)
{
	if (Icon && Quantity&&ItemIcon)
	{
		ItemIcon->SetBrushFromTexture(Icon);
		ItemIcon->SetVisibility(ESlateVisibility::Visible);
		//QuantityText->SetText(FText::AsNumber(Quantity));
		//QuantityText->SetVisibility(ESlateVisibility::Visible);	
		
	}



}

void UQuickSlotWidget::AddQuantity(int32 Number)
{
	
	QuantityText->SetText(FText());


}

void UQuickSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	MainCharacter = Cast<AMainCharacter>(GetOwningPlayerPawn());
	

	if (SlotButton)
	{
		SlotButton->OnClicked.AddDynamic(this, &UQuickSlotWidget::HandleButtonClicked);
	}


	

}

void UQuickSlotWidget::HandleButtonClicked()
{

	OnSlotClicked.Broadcast(SlotIndex);

}

void UQuickSlotWidget::HandleDownMouseClicked()
{

	//UE_LOG(LogTemp, Warning, TEXT("down mouse clicked!"));


}

FReply UQuickSlotWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	UE_LOG(LogTemp, Warning, TEXT("down mouse clicked! %d"),SlotIndex);

	if (MainCharacter)
	{
		MainCharacter->DropFromIndex(SlotIndex);
	}

	return FReply::Handled();
}


void UQuickSlotWidget::SetSliceRotation(float Angle)
{
	if (SliceImage)
	{
		FWidgetTransform TransformData;
		TransformData.Angle = Angle;
		SetRenderTransform(TransformData);
		//SliceImage->SetRenderTransform(TransformData);
		//ItemIcon->SetRenderTransform(TransformData);
	}
}

