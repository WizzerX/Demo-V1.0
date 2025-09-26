// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/MainWidget.h"
#include "Components/ProgressBar.h"
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

void UMainWidget::UpdateHungerUI(float value)
{
	HungerBar->SetPercent(value);
}

void UMainWidget::UpdateThirstUI(float value)
{
	ThirstBar->SetPercent(value);
}
