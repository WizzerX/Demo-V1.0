// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget/QuickSlotWidget.h"
#include "Item/Interactable/PickupableItem.h"
#include "QuickSlotBarWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTestDelegate, int32, score);

/**
 * 
 */
UCLASS()
class DEMO_API UQuickSlotBarWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnyWhere)
		TArray<int32>SlotArray = { 0,1,2,3,4,5 };

	
	UPROPERTY()
	UQuickSlotWidget* QuickSlotWidget;

	UFUNCTION(BlueprintCallable)
		void SetSliceRotation(float Angle);



	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* Canvas;
	

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<UQuickSlotWidget*>RadialWheel;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UQuickSlotWidget>QuickRadialSlotClass;


	void RightClicked();

	UFUNCTION()
	void OnSlotClicked(int32 index);

	virtual void NativeConstruct() override;

	void AddWidget();

	


	UPROPERTY(VisibleAnyWhere,BlueprintReadOnly)
	class AMainCharacter* CharacterRef;

	UFUNCTION()
	void UpdateUIAt(int32 index,const FInventoryItemData& Data);

	


	

	FTestDelegate TestDelegate;






	UFUNCTION()
	void ChangeScore(int32 score);
};
