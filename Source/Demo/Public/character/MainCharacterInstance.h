// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MainCharacter.h"
//#include "Item/Weapon/WeaponType.h"
#include "MainCharacterInstance.generated.h"

UENUM(BlueprintType)
enum class AnimationState : uint8
{

	Runing UMETA(DisplayName = "Run"),
	Idle UMETA(DisplayName = "IDLE")

};


/**
 * 
 */
UCLASS()
class DEMO_API UMainCharacterInstance : public UAnimInstance
{
	GENERATED_BODY()


public:
	
	virtual void  NativeInitializeAnimation() override;
	

	

	UFUNCTION(BlueprintCallable)
	void UpdateAnimationProperties(float DeltaTime);


private:
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly , Category = movemment, meta = (AllowPrivateAccess=true))
	  AMainCharacter* MainCharacter;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category =movement,meta=(AllowPrivateAccess=true))
	float speed=0.0;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = movement, meta = (AllowPrivateAccess = true))
	bool bIsInAir;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = movement, meta = (AllowPrivateAccess = true))
	bool bAccelerating;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = movement, meta = (AllowPrivateAccess = true))
	float Direction;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = movement, meta = (AllowPrivateAccess = true))
	bool bCrouching;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = movement, meta = (AllowPrivateAccess = true))
	AnimationState AnimationState;




};
