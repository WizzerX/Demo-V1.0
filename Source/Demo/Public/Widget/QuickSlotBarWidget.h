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
	UPROPERTY(meta = (BindWidget))
	class	UUniformGridPanel* Grid;

	UPROPERTY()
	UQuickSlotWidget* QuickSlotWidget;

	
	

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<UQuickSlotWidget*>SlotBar;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UQuickSlotWidget>QuickSlotClass;




	virtual void NativeConstruct() override;

	void AddWidget();

	class AMainCharacter* CharacterRef;

	UFUNCTION()
	void UpdateUIAt(int32 index,const FInventoryItemData& Data);

	


	

	FTestDelegate TestDelegate;






	UFUNCTION()
	void ChangeScore(int32 score);
};
