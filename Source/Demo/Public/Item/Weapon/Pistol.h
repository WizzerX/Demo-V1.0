// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/Weapon/BaseWeapon.h"
#include "Pistol.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_API APistol : public ABaseWeapon
{
	GENERATED_BODY()
public:
	APistol();

	virtual void FireTheWeapon() override;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnyWhere,BlueprintReadWrite)
	USkeletalMeshComponent* WeaponMesh;


private:
	FRotator InitRot;
	FRotator FinalRot;
	float AlphaValue=0.0f;
	float RecoilSpeed;
	float CurrentRecoilTime;
	float RecoilDuration ;
};
