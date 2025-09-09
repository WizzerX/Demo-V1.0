// Fill out your copyright notice in the Description page of Project Settings.


#include "../../Demo/Charcter/MainCharacterController.h"
#include "Widget/SlotWidget.h"
#include "Components/Widget.h"
void AMainCharacterController::BeginPlay()
{
    Super::BeginPlay();

    if (QuickSlotClass)
    {
       UUserWidget* widget = CreateWidget<UUserWidget>(this, QuickSlotClass);
       QuickSlotWidget = widget;
        if (QuickSlotWidget)
        {
            QuickSlotWidget->AddToViewport();
        }
    }


}

AMainCharacterController::AMainCharacterController()
{


}

