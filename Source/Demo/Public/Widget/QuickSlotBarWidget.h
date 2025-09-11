// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget/QuickSlotWidget.h"
#include "QuickSlotBarWidget.generated.h"


/**
 * 
 */
UCLASS()
class DEMO_API UQuickSlotBarWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	class	UUniformGridPanel* Grid;




	
	

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<UQuickSlotWidget*>SlotBar;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UQuickSlotWidget>QuickSlotClass;


	UPROPERTY()
	UQuickSlotWidget* QuickSlotWidget;

	virtual void NativeConstruct() override;

	void AddWidget();

	void UpdateUIAt(int32 index, UTexture2D* icon, int32 Quantity);


	
};
