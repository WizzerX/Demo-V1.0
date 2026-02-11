// Fill out your copyright notice in the Description page of Project Settings.


#include "character/MainCharacterController.h"
#include "Components/Widget.h"
#include "Widget/MainWidget.h"
void AMainCharacterController::BeginPlay()
{
    Super::BeginPlay();
    MainWidget = CreateWidget<UMainWidget>(this, QuickSlotClass);

    if (MainWidget)
    {
        MainWidget->AddToViewport();
       

    }
   

}

AMainCharacterController::AMainCharacterController()
{
 


}

void AMainCharacterController::PlayerReadingNote(UUserWidget* mywidget)
{
   
    FInputModeGameAndUI InputeMode;
    InputeMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
    InputeMode.SetWidgetToFocus(mywidget->TakeWidget());
    SetIgnoreMoveInput(true);
    SetInputMode(InputeMode);
   


}

void AMainCharacterController::PlayerStopReading(UUserWidget* widget)
{
    FInputModeGameOnly GameMode;
    SetInputMode(GameMode);
    SetIgnoreMoveInput(false);
    widget->RemoveFromParent();
}

void AMainCharacterController::HideInventory()
{
    MainWidget->RadialWheel->SetVisibility(ESlateVisibility::Hidden);
    bShowMouseCursor = false;
    SetInputMode(FInputModeGameOnly());

}
void AMainCharacterController::ShowInventory()
{
    MainWidget->RadialWheel->SetVisibility(ESlateVisibility::Visible);
    bShowMouseCursor = true;

    

    SetInputMode(FInputModeGameAndUI());


}

void AMainCharacterController::UpdateHealth(float value)
{
    MainWidget->UpdateHealthUI(value);



}

void AMainCharacterController::UpdateStamina(float value)
{
    MainWidget->UpdateStaminaUI(value);
}

void AMainCharacterController::UpdateHungerAndThirst(float HungerValue, float ThirstValue)
{
    MainWidget->SurvivialDelegate.Broadcast(HungerValue, ThirstValue);


}



void AMainCharacterController::UpdateRadioactive(float value)
{

    MainWidget->UpdateRadioactiveUI(value);
}


