// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/Weapon/BaseWeapon.h"
#include "Rifile.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_API ARifile : public ABaseWeapon
{
	GENERATED_BODY()


public:

	ARifile();
	FTimerHandle Timer;

	virtual void FireTheWeapon() override;
	virtual void StartFire() override;
	virtual void StopFire() override;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		float FireRate;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		UParticleSystem* MuzzleFlash;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		TSubclassOf<UCameraShakeBase>WeaponFireShake;

	FVector Loc;
	FRotator Rot;
};
