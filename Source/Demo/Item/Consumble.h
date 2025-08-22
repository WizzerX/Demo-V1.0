// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Demo/Item/PickupableItem.h"
#include "Consumble.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_API AConsumble : public APickupableItem
{
	GENERATED_BODY()





public:
	

	virtual bool IsPickable()const { return false; }


private:
	virtual void Interact(AMainCharacter* Character) override;

	AConsumble();
};
