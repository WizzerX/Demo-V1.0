// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseEnemy.generated.h"

UENUM(BlueprintType)
enum class EEnenmyState :uint8
{
	IDLE,
	ALERT,
	CHASE,
	FLEE,
	ATTACK,
	FEED,
	REST



};





UCLASS()
class DEMO_API ABaseEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	FTimerHandle DistanceTime;
	ACharacter* TargetPawn;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	EEnenmyState EnemyState;


	void Roam();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UWidgetComponent* WidgetComponent;



	UFUNCTION(BlueprintCallable)
	void Chase();


	void Flee(ACharacter* Character);

	UFUNCTION(BlueprintCallable)
	void Attack();

	UFUNCTION(BlueprintCallable)
	void CheckDistanceToPlayer();


	UFUNCTION()
	void OnPerceptionUpdate(const TArray<AActor*>& UpdatedActors);
	
class	AAIController* EnemyController;

UPROPERTY(EditAnywhere, BlueprintReadWrite)
class	UAISenseConfig_Sight* AIConfig;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int Heath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UAIPerceptionComponent* PerceptionComponent;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
class	UAIPerceptionStimuliSourceComponent* PerceptionStimuliSourceComponent;

UPROPERTY(VisibleAnyWhere,BlueprintReadOnly,Category="AI")
bool bAttackable;


UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "AI")
bool bAttacking;

class UBlackboardComponent* BlackBoardComponent;

};
