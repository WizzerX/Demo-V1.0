// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/Weapon/BaseWeapon.h"
#include "Molotov.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_API AMolotov : public ABaseWeapon
{
	GENERATED_BODY()


public:
	virtual void FireTheWeapon() override;
		AMolotov();

private:
	virtual void SetItemProperties(EItemState State) override;
	//UFUNCTION()
		virtual void OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			FVector NormalImpulse, const FHitResult& Hit)override;
		void BlastMolotov();

	class	UAnimInstance* CharacterAnimInstance;

	bool bThrowen = false;
public:
		UPROPERTY(EditAnyWhere,BlueprintReadWrite)
		UNiagaraSystem* FlameRadius;

		UFUNCTION(BlueprintCallable)
			void MolotovLogic();

};
