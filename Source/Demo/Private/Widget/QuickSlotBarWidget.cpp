// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/QuickSlotBarWidget.h"
#include "Components/Widget.h"
#include "Widget/QuickSlotWidget.h"
#include "Components/PanelWidget.h" 
#include <iostream>
#include "Components/UniformGridPanel.h"
#include "Components/SizeBox.h"

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


}

void UQuickSlotBarWidget::AddWidget()
{
	



}

void UQuickSlotBarWidget::UpdateUIAt(int32 index, UTexture2D* icon, int32 Quantity)
{
	if (SlotBar.IsValidIndex(index)&& icon && Quantity)
	{
		SlotBar[index]->UpdateUI(icon, Quantity);
		UE_LOG(LogTemp, Log, TEXT("Update UI Sucess!: %d" ),index);
		
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Update UI Failed!"));
	}

}
