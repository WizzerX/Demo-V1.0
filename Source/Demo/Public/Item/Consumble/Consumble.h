// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/Interactable/PickupableItem.h"
#include "Consumble.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_API AConsumble : public APickupableItem
{
	GENERATED_BODY()





public:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float thirst = 49;

	virtual bool IsPickable()const { return true; }
	void UseConsumble();

private:
	virtual void Interact(AMainCharacter* Character) override;



	AConsumble();
};
