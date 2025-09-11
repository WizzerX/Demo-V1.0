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
UCLASS()
class DEMO_API UMainWidget : public UUserWidget
{
	GENERATED_BODY()



public:


	UPROPERTY(meta = (BindWidget))
	class UQuickSlotBarWidget* QuickSlotBar;

	

	
};
