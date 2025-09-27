// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "Widget/QuickSlotBarWidget.h"
#include "MainWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FHungerThirstDelegate, float ,HungerValue, float ,ThirstValue);

/**
 * 
 */
class UProgressBar;

UCLASS()
class DEMO_API UMainWidget : public UUserWidget
{
	GENERATED_BODY()



public:



	virtual void NativeConstruct() override;

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

	FHungerThirstDelegate SurvivialDelegate;

	UFUNCTION()
	void UpdateHungerAndThirst(float HungerValue, float ThirstValue);


	void UpdateHealthUI(float value);
	void UpdateStaminaUI(float value);
	void UpdateRadioactiveUI(float value);
	
};
