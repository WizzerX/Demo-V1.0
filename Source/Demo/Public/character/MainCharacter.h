// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "MainCharacter.generated.h"


UCLASS()
class DEMO_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess="true"))
	class USpringArmComponent* springArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* camera;


private:
	void EPressed();
	void EReleased();



public:
	
	AMainCharacter();
	bool bIsReading = false;
protected:
	
	virtual void BeginPlay() override;


	void MoveRight(float value);
	void MoveForward(float value);
	void TurnAtRate(float value);
	void LookUpAtRate(float value);
	void Crouch();
	void StopCrouch();
	void Fire();
	void DropItem();
	void Slot1();
	void Slot2();
	void Slot3();
	void Slot4();


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void  CurrentTraceItem();

	

	void Equip();



	/*Only For Testing*/
	void Pickup();

	bool bAttach = false;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;


	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = movement, meta = (AllowPrivateAccess = true))
	USceneComponent* AttachPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Inventroy, meta = (AllowPrivateAccess = true))
   class	UInventoryComponent* InventoryComponent;


	

public:
	bool bCrouch = false;
	class  APickupableItem* PreviousItem;
	 class APickupableItem* CurrentItem;
	 class APickupableItem* PickupableItem;
	 bool bInteractable=false;
	 bool bEPressed = false;
	



	 UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	 float Health = 100;

	 UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	 float Thirst = 100;

	 UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	 float Hunger = 100;

	 UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	 float Radioactive = 100;


	 UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	 float Stamina = 100;

	 void TakeHealth(float value);
	 void TakeStamina(float value);
	 void TakeRadioactive(float value);
	 void TakeHunger(float value);
	 void TakeThirst(float value);




};
