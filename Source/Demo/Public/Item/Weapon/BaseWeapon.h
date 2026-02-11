// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/Interactable/PickupableItem.h"
#include "Item/Weapon/WeaponType.h"
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAnimMontage* AttackAnimation;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//	USoundBase* AttackSound;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	///USkeletalMeshComponent* WeaponMesh;

public:
	UPROPERTY(VisibleAnyWhere,BlueprintReadOnly)
	bool bActiveRecoil = false;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly)
	bool bRecoverRecoil = false;


	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FName MuzzleName;

	void PlayAttackMontage();

public:
	virtual void FireTheWeapon() {};
	
	virtual  void StartFire() {};
	virtual void StopFire() {};



	bool bAutomatic = false;



	//UPROPERTY(EditAnyWhere,BlueprintReadWrite,Category="WeaponType")
	//EItemType ItemType=EItemType::None;

	UPROPERTY(EditAnyWhere)
		UAnimMontage* FireAnimation;



FORCEINLINE EItemType GetItemType(){ return ItemType; }
FORCEINLINE USkeletalMeshComponent* GetWeaponMesh() { return WeaponMesh; }



};
