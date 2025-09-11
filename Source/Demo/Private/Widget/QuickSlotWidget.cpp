// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/QuickSlotWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/SizeBox.h"

void UQuickSlotWidget::UpdateUI(UTexture2D* Icon, int32 Quantity)
{
	if (Icon && Quantity&&ItemIcon)
	{
		ItemIcon->SetBrushFromTexture(Icon);
		ItemIcon->SetVisibility(ESlateVisibility::Visible);
		QuantityText->SetText(FText::AsNumber(Quantity));
		QuantityText->SetVisibility(ESlateVisibility::Visible);
	}



}

void UQuickSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	





}
