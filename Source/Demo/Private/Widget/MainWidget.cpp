// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/MainWidget.h"
#include "Components/ProgressBar.h"
void UMainWidget::NativeConstruct()
{
	Super::NativeConstruct();
	SurvivialDelegate.AddDynamic(this, &UMainWidget::UpdateHungerAndThirst);



}
void UMainWidget::UpdateHungerAndThirst(float Hunger, float Thirst)
{
	HungerBar->SetPercent(Hunger);
	ThirstBar->SetPercent(Thirst);


}
void UMainWidget::UpdateHealthUI(float value)
{
	HealthBar->SetPercent(value);



}

void UMainWidget::UpdateStaminaUI(float value)
{
	StaminaBar->SetPercent(value);
}

void UMainWidget::UpdateRadioactiveUI(float value)
{
	RadioactiveBar->SetPercent(value);


}

