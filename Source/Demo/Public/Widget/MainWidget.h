// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "Widget/QuickSlotBarWidget.h"
#include "MainWidget.generated.h"

/**
 * 
 */
class UProgressBar;

UCLASS()
class DEMO_API UMainWidget : public UUserWidget
{
	GENERATED_BODY()



public:


	UPROPERTY(meta = (BindWidget))
	class UQuickSlotBarWidget* QuickSlotBar;

	UPROPERTY(meta = (BindWidget))
	class	UProgressBar* HealthBar;

	UPROPERTY(meta = (BindWidget))
	class	UProgressBar* ThirstBar;

	UPROPERTY(meta = (BindWidget))
	class	UProgressBar* RadioactiveBar;

	UPROPERTY(meta = (BindWidget))
	class	UProgressBar* StaminaBar;


	UPROPERTY(meta = (BindWidget))
	class	UProgressBar* HungerBar;

	void UpdateHealthUI(float value);
	void UpdateStaminaUI(float value);
	void UpdateRadioactiveUI(float value);
	void UpdateHungerUI(float value);
	void UpdateThirstUI(float value);
};
