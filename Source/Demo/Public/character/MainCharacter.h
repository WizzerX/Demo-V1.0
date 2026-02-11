// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Item/Weapon/BaseWeapon.h"
#include "Item/Weapon/WeaponType.h"
#include "MainCharacter.generated.h"







UCLASS()
class DEMO_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()


public:
	


	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* camera;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly)
		bool bInventoryIsOpen = false;


class		AMainCharacterController* MainPlayerController;

private:
	void EPressed();
	void EReleased();
class	UMainCharacterInstance* CharacterInstance;


public:
	
	AMainCharacter();
	bool bIsReading = false;

	bool bShift = false;
protected:
	
	virtual void BeginPlay() override;


	void MoveRight(float value);
	void MoveForward(float value);
	void TurnAtRate(float value);
	void LookUpAtRate(float value);
	void Crouch();
	void StopCrouch();
	void Fire();
	void StopFire();
	void DropItem();
	void Slot1();
	void Slot2();
	void Slot3();
	void Slot4();
	void Unequip();
	void Shift();
	void ScopeOn();
	void Inventory();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	void AddControllerYawInput(float Val);


	void  CurrentTraceItem();

	

	void Equip();
	void PlayCameraShake(TSubclassOf<UCameraShakeBase> WeaponShake);


	/*Only For Testing*/
	void Pickup();

	bool bAttach = false;

	UPROPERTY(EditAnyWhere,BlueprintReadWrite)
	bool bTurnLeft = false;
	
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	bool bTurnRigt = false;




public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;


	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = movement, meta = (AllowPrivateAccess = true))
	USceneComponent* AttachPoint;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		TSubclassOf<UCameraShakeBase>CameraShake;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Inventroy, meta = (AllowPrivateAccess = true))
   class	UInventoryComponent* InventoryComponent;

   UPROPERTY(VisibleAnyWhere, BlueprintReadOnly)
   EItemType CurrentWeaponType = EItemType::None;
	

public:
	bool bFire = false;
	bool bCrouch = false;
	class  APickupableItem* PreviousItem;
	 class APickupableItem* CurrentItem;
	 class APickupableItem* PickupableItem;
	 bool bInteractable=false;
	 bool bEPressed = false;

	
	 APickupableItem* CurrentEquiped;

	 ABaseWeapon* CurrentWeapon;
	 int CurrentSlot;
	 




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
	 void UpdateHungerAndThirst();

	 FTimerHandle HungerAndThirstTimer;

	 FORCEINLINE UCameraComponent* GetCameraComponent() { return camera; }


public:
	void EquipFromIndex(int32 index);
	void DropFromIndex(int32 index);


};
