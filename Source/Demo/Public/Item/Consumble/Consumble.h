// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/Interactable/PickupableItem.h"
#include "Consumble.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EConsumbleType :uint8
{
	Thirst,
	Hunger,
	RadioActiveHeal,
	HealthHeal,
	custom


};





UCLASS()
class DEMO_API AConsumble : public APickupableItem
{
	GENERATED_BODY()





public:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float value = 49;

	virtual bool IsPickable()const { return true; }
	void UseConsumble();

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	EConsumbleType ConsumbleType;

private:
	virtual void Interact(AMainCharacter* Character) override;
	

	AConsumble();
};
