// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/Interactable/PickupableItem.h"
#include "BaseWeapon.generated.h"
/**
 * 
 */
UCLASS()
class DEMO_API ABaseWeapon : public APickupableItem
{
	GENERATED_BODY()


public:

	ABaseWeapon();

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
class	USoundBase* ShootSound;

UPROPERTY(EditAnywhere, BlueprintReadWrite)
class UNiagaraSystem* GunFlash;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float VerticleKick;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HorizontalKick;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RecoverSpeed;


	
};
