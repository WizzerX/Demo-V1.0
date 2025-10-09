// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/Interactable/PickupableItem.h"
#include "Notes.generated.h"

/**
 * 
 */
class USoundBase;

UCLASS()
class DEMO_API ANotes : public APickupableItem
{
	GENERATED_BODY()

private:

	ANotes();

	virtual bool IsPickable()const { return false; }

	virtual void Interact(AMainCharacter* Character) override;
	

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "widget")
	UUserWidget* NoteWidget;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "widget")
	TSubclassOf<UUserWidget>  NoteWidgetClass;

private:

	void StopReading();
	
	UPROPERTY(EditAnyWhere)
	USoundBase* PageSound;
};
