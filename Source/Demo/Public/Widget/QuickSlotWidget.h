// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "QuickSlotWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSlotClicked, int32, Index);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMouseDownClicked, int32, Index2);

/**
 * 
 */
UCLASS()
class DEMO_API UQuickSlotWidget : public UUserWidget
{
	GENERATED_BODY()




public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
		int32 SlotIndex;

	// Dispatcher
	UPROPERTY(BlueprintAssignable)
		FOnSlotClicked OnSlotClicked;

	UPROPERTY(BlueprintAssignable)
		FOnMouseDownClicked OnMouseDownClicked;

	UFUNCTION()
		void HandleButtonClicked();

	UFUNCTION()
		void HandleDownMouseClicked();



	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly)
class		AMainCharacter* MainCharacter;



	virtual FReply NativeOnMouseButtonDown(
		const FGeometry& InGeometry,
		const FPointerEvent& InMouseEvent
	) override;



	UPROPERTY(meta = (BindWidget))
class UImage* SliceImage;


	UFUNCTION(BlueprintCallable)
		void SetSliceRotation(float Angle);
	
	UPROPERTY(meta = (BindWidget))
	class UImage* ItemIcon;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* QuantityText;

	// Button in widget
	UPROPERTY(meta = (BindWidget))
	class UButton* SlotButton;


	UPROPERTY(meta = (BindWidget))
		class UBorder* Border2;

	
	void UpdateUI(UTexture2D* Icon, int32 Quantity);
	
	void AddQuantity(int32 Number);

	virtual void NativeConstruct() override;
	
	
};
