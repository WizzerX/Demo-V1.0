// Fill out your copyright notice in the Description page of Project Settings.


#include "../../Demo/Charcter/MainCharacterController.h"
#include "Components/Widget.h"
#include "Widget/QuickSlotWidget.h"
void AMainCharacterController::BeginPlay()
{
    Super::BeginPlay();
    SlotWidget = CreateWidget<UQuickSlotWidget>(this, QuickSlotClass);

    if (SlotWidget)
    {
        SlotWidget->AddToViewport();


    }
   

}

AMainCharacterController::AMainCharacterController()
{
 


}

