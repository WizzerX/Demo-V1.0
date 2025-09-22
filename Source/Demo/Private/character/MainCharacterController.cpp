// Fill out your copyright notice in the Description page of Project Settings.


#include "character/MainCharacterController.h"
#include "Components/Widget.h"
#include "Widget/MainWidget.h"
void AMainCharacterController::BeginPlay()
{
    Super::BeginPlay();
    SlotWidget = CreateWidget<UMainWidget>(this, QuickSlotClass);

    if (SlotWidget)
    {
        SlotWidget->AddToViewport();


    }
   

}

AMainCharacterController::AMainCharacterController()
{
 


}

