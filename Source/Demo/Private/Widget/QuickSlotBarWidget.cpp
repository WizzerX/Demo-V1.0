// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/QuickSlotBarWidget.h"
#include "Components/Widget.h"
#include "Widget/QuickSlotWidget.h"
#include "Components/UniformGridPanel.h" 
#include "character/MainCharacter.h"
#include "Item/Inventory/InventoryComponent.h"
#include "Components/TextBlock.h"
#include "Item/Interactable/PickupableItem.h"
#include "Demo/Public/Widget/QuickSlotWidget.h"
#include "Components/Image.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"


void UQuickSlotBarWidget::SetSliceRotation(float Angle)
{
	


}



void UQuickSlotBarWidget::RightClicked()
{




}

void UQuickSlotBarWidget::OnSlotClicked(int32 index)
{
	UE_LOG(LogTemp, Warning, TEXT("Clicked Slot Index: %d"), index);

	UE_LOG(LogTemp, Warning, TEXT("Rock!"));
	if (CharacterRef)
	{
		CharacterRef->EquipFromIndex(index);
	}





}

void UQuickSlotBarWidget::NativeConstruct()
{
	Super::NativeConstruct();

	CharacterRef = Cast<AMainCharacter>(GetOwningPlayer());
	

	RadialWheel.Empty();

	const int32 SlotCount = 6;
	const float Radius = 165.f;
	const FVector2D Center(1000.f, 500.f); // Adjust to your canvas size
	const float AngleStep = 360.f / SlotCount;

	for (int32 i = 0; i < SlotCount; i++)
	{
		QuickSlotWidget = CreateWidget<UQuickSlotWidget>(this, QuickRadialSlotClass);
		
		if (!QuickSlotWidget) continue;
		QuickSlotWidget->SlotIndex = i; // ?? THIS IS THE KEY

		QuickSlotWidget->OnSlotClicked.AddDynamic(this, &UQuickSlotBarWidget::OnSlotClicked);

		RadialWheel.Add(QuickSlotWidget);

		if (!Canvas)
		{
			UE_LOG(LogTemp, Error, TEXT("Canvas is NULL! Check BindWidget name."));
			return;
		}




	
		UCanvasPanelSlot* CanvasSlot = Canvas->AddChildToCanvas(QuickSlotWidget);

		if (CanvasSlot)
		{
			float AngleDeg = i * AngleStep;
			float AngleRad = FMath::DegreesToRadians(AngleDeg);

			float X = FMath::Cos(AngleRad) * Radius;
			float Y = FMath::Sin(AngleRad) * Radius;

			CanvasSlot->SetAlignment(FVector2D(0.5f, 0.5f));
			CanvasSlot->SetAutoSize(true);
			CanvasSlot->SetPosition(Center + FVector2D(X, Y));

			// Rotate slice only
			float SliceAngle = AngleDeg +90;
			QuickSlotWidget->SetSliceRotation(SliceAngle);
			
		}

	}

	// Delegate binding
	CharacterRef = Cast<AMainCharacter>(GetOwningPlayerPawn());
	if (CharacterRef)
	{
		CharacterRef->InventoryComponent->SlotWidgetDelegate.AddDynamic(
			this, &UQuickSlotBarWidget::UpdateUIAt);
	}

}

void UQuickSlotBarWidget::AddWidget()
{
	
	


}

void UQuickSlotBarWidget::UpdateUIAt(int32 index,const FInventoryItemData& Data)
{
	
	

	if (RadialWheel.IsValidIndex(index))
	{
		UE_LOG(LogTemp, Warning, TEXT("INDEX UPDATE UI:%d"), index);
		
		if (Data.Quantity <= 0)
		{
		RadialWheel[index]->QuantityText->SetText(FText::AsNumber(0));
	
		RadialWheel[index]->ItemIcon->SetVisibility(ESlateVisibility::Hidden);
	
		RadialWheel[index]->QuantityText->SetVisibility(ESlateVisibility::Visible);
		UE_LOG(LogTemp, Warning, TEXT("Deleate the slot"), index);
		
			
		}


		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Slot Updated success !"), index);
			RadialWheel[index]->ItemIcon->SetBrushFromTexture(Data.Icon);
			RadialWheel[index]->ItemIcon->SetVisibility(ESlateVisibility::Visible);
			RadialWheel[index]->QuantityText->SetText(FText::AsNumber(Data.Quantity));
		
		}
	}


	
}


void UQuickSlotBarWidget::ChangeScore(int32 score)
{


	UE_LOG(LogTemp,Error, TEXT("INDEX UPDATE UI:%d"),score);

}
