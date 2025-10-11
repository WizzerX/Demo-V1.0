// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EnemyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_API UEnemyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnyWhere,BlueprintReadWrite)
	float Speed;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	bool bDead = false;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	bool bIsInAir = false;
	
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	bool bIsMoving = false;

	

	
};
