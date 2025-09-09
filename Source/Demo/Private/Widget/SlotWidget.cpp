// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/SlotWidget.h"
#include "Components/TextBlock.h"
#include "Components/BrushComponent.h"
#include "Components/Image.h"
#include "Styling/SlateBrush.h"

void USlotWidget::UpdatUI(UTexture2D* NewTexture, int32 NewQuantity)
{
	
	if (NewTexture)
	{
		ItemImage->SetBrushFromTexture(NewTexture);
		QuantityText->SetText(FText::AsNumber(NewQuantity));
		UE_LOG(LogTemp, Warning, TEXT("update UI"));

	}

	

}
