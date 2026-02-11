// Fill out your copyright notice in the Description page of Project Settings.


#include "character/MainCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Controller.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "DrawDebugHelpers.h"
#include "Components/SceneComponent.h"
#include "Components/WidgetComponent.h"
#include <Kismet/GameplayStatics.h>
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Item/Interactable/PickupableItem.h"
#include "Item/Inventory/InventoryComponent.h"
#include "Components/Widget.h"
#include "Widget/MainWidget.h"
#include "Widget/QuickSlotBarWidget.h"
#include "character/MainCharacterController.h"
#include "TimerManager.h"
#include "Demo/Public/Item/Weapon/BaseWeapon.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "Item/Weapon/BaseWeapon.h"
#include <Kismet/KismetMathLibrary.h>
#include <character/MainCharacterInstance.h>
AMainCharacter::AMainCharacter()
{
 	
	PrimaryActorTick.bCanEverTick = true;
	
	


	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camerarra"));	
	camera->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);


	AttachPoint = CreateDefaultSubobject<USceneComponent>(TEXT("AttachPoint"));

	AttachPoint->SetupAttachment(GetRootComponent());
	

	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));




	

	bTurnLeft = false;
	bTurnRigt = false;
	
}


void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(HungerAndThirstTimer, this, &AMainCharacter::UpdateHungerAndThirst, 1, true, 1.f);
	if (bShift)
	{
		bShift = false;
		GetCharacterMovement()->MaxWalkSpeed = 300;

		return;
	}
	MainPlayerController = Cast<AMainCharacterController>(UGameplayStatics::GetPlayerController(this, 0));

	CharacterInstance = Cast<UMainCharacterInstance>(GetMesh()->GetAnimInstance());


}

void AMainCharacter::MoveRight(float value)
{
	if ((Controller != nullptr) && (value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, value);
	
	}


}

void AMainCharacter::MoveForward(float value)
{
	if ((Controller != nullptr) && (value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, value);
		
	}



}

void AMainCharacter::TurnAtRate(float value)
{
	AddControllerYawInput(value * BaseTurnRate * GetWorld()->GetDeltaSeconds());


}

void AMainCharacter::LookUpAtRate(float value)
{
	AddControllerPitchInput(value * BaseLookUpRate * GetWorld()->GetDeltaSeconds());


}

void AMainCharacter::Crouch()
{
	
	UE_LOG(LogTemp, Warning, TEXT("Crouching"));

	if (!bCrouch)
	{
		//GetCapsuleComponent()->SetCapsuleHalfHeight(88);
		GetCharacterMovement()->MaxWalkSpeed = 200.f;
		float CapsuleHeight = GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight();
		UE_LOG(LogTemp, Warning, TEXT("Capsule Half Height: %f"), CapsuleHeight);
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("crouching"));
		bCrouch = true;
		return;
	}
	if (bCrouch)
	{
		bCrouch = false;
		GetCharacterMovement()->MaxWalkSpeed = 600.f;
		//GetCapsuleComponent()->SetCapsuleHalfHeight(88);
		UE_LOG(LogTemp, Warning, TEXT("Stop_Crouching"));
		return;

	}


}

void AMainCharacter::StopCrouch()
{
	

}

void AMainCharacter::Fire()
{
	
	bFire = true;
		FVector StartLoc = camera->GetComponentLocation();
		FVector ForwardLoc = camera->GetForwardVector();
		FVector EndLoc = StartLoc + ForwardLoc * 800;

		FHitResult HitResult;

		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);


		GetWorld()->LineTraceSingleByChannel(HitResult, StartLoc, EndLoc, ECollisionChannel::ECC_WorldStatic, Params);

		//DrawDebugLine(GetWorld(), StartLoc, EndLoc, FColor::Red, false, 5.f);
		if (CurrentEquiped->CheckWeapon(EItemCategory::IC_WEAPON))
		{

			ABaseWeapon* Weapon = Cast<ABaseWeapon>(CurrentEquiped);
			if (Weapon)
			{
				Weapon->FireTheWeapon();
				Weapon->PlayAttackMontage();

			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("CAST FAILED!"));
			}
		}
	
}

void AMainCharacter::StopFire()
{
	bFire = false;
	ABaseWeapon* Weapon = Cast<ABaseWeapon>(CurrentEquiped);
	if (Weapon)
	{
		Weapon->StopFire();

	}
	UE_LOG(LogTemp, Warning, TEXT("Stop Fire!"));

}

void AMainCharacter::DropItem()
{
	
	if (!CurrentEquiped )return;

	
	UE_LOG(LogTemp, Warning, TEXT("Drop THE ITEM"));
	
	if (CurrentEquiped && !bIsReading)
	{
		const FInventoryItemData& Item = InventoryComponent->GetItemAt(CurrentSlot);
		CurrentEquiped->GetMesh()->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
		
		InventoryComponent->RemoveItem(Item);
	


		CurrentEquiped->SetItemState(EItemState::EIS_Falling);
		CurrentWeaponType = EItemType::None;
		CurrentEquiped = nullptr;
		PickupableItem = nullptr;
		CurrentItem = nullptr;
		PreviousItem = nullptr;
	 
	}
	

	

}

void AMainCharacter::Slot1()
{
	if (!bIsReading)
	{
		UE_LOG(LogTemp, Warning, TEXT("Slot1 is pressed!"));


		const	FInventoryItemData& item = InventoryComponent->GetItemAt(0);


		// Spawn actor

		FActorSpawnParameters Params;
		Params.Owner = this;
		Params.Instigator = GetInstigator();
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
		if (CurrentEquiped)
		{
			CurrentEquiped->Destroy();
		}


		if (item.Quantity != 0)
		{


			
			FName SocketName = item.SocketName;
			auto spawn= GetWorld()->SpawnActor<APickupableItem>(item.ItemActorClass, GetMesh()->GetSocketLocation(SocketName), GetMesh()->GetSocketRotation(SocketName), Params);
			spawn->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName(SocketName));
			
			
			  
			spawn->SetItemState(EItemState::EIS_Equipped);
			CurrentEquiped = spawn;
			CurrentSlot = 0;

			
				if (CurrentEquiped)
				{
					//CurrentWeaponType=CurrentEquiped
					UE_LOG(LogTemp, Warning, TEXT("Magic is happenigng!"));
					//CurrentWeaponType=CurrentEquiped->GetWeaponType()
					 CurrentWeaponType= CurrentEquiped->ItemType;
					
					//FVector Loc= CurrentWeapon->GetWeaponMesh()->GetSocketLocation(CurrentWeapon->SlotName);
					//FRotator Roc = CurrentWeapon->GetWeaponMesh()->GetSocketRotation(CurrentWeapon->SlotName);
					
				}
				
					
				
					
			
			/*else if (CurrentEquiped->GetItemCategory() != EItemCategory::IC_WEAPON)
			{
				CurrentWeaponType = CurrentWeapon->GetItemType();


			}
			*/
			
		}
	}
}

void AMainCharacter::Slot2()
{
	
	if (!bIsReading)
	{
		UE_LOG(LogTemp, Warning, TEXT("Slot2  is pressed!"));
		const FInventoryItemData& item = InventoryComponent->GetItemAt(1);

		if (CurrentEquiped)
		{
			CurrentEquiped->Destroy();
		}



		// Spawn actor
		FActorSpawnParameters Params;
		Params.Owner = this;
		Params.Instigator = GetInstigator();
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		if (item.Quantity != 0)
		{
			auto spawn = GetWorld()->SpawnActor<APickupableItem>(item.ItemActorClass, this->GetTargetLocation(), FRotator::ZeroRotator, Params);
			spawn->AttachToComponent(AttachPoint, FAttachmentTransformRules::SnapToTargetIncludingScale, spawn->SlotName);
			FQuat quat(FRotator(172.799545, 104.399696, 0.0));

			spawn->SetActorRelativeRotation(quat);
			spawn->SetItemState(EItemState::EIS_Equipped);
			CurrentEquiped = spawn;
			CurrentSlot = 1;

		}
	}

}

void AMainCharacter::Slot3()
{
	
	if (!bIsReading)
	{
		UE_LOG(LogTemp, Warning, TEXT("Slot3  is pressed!"));
		const FInventoryItemData& item = InventoryComponent->GetItemAt(2);

		if (CurrentEquiped)
		{
			CurrentEquiped->Destroy();
		}




		// Spawn actor
		FActorSpawnParameters Params;
		Params.Owner = this;
		Params.Instigator = GetInstigator();
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		if (item.Quantity != 0)
		{
			auto spawn = GetWorld()->SpawnActor<APickupableItem>(item.ItemActorClass, this->GetTargetLocation(), FRotator::ZeroRotator, Params);
			spawn->AttachToComponent(AttachPoint, FAttachmentTransformRules::SnapToTargetIncludingScale, FName("NONE"));
			FQuat quat(FRotator(172.799545, 104.399696, 0.0));

			spawn->SetActorRelativeRotation(quat);
			spawn->SetItemState(EItemState::EIS_Equipped);
			CurrentEquiped = spawn;
			CurrentSlot = 2;
		}
	}

}

void AMainCharacter::Slot4()
{
	UE_LOG(LogTemp, Warning, TEXT("Slot4  is pressed!"));
	const FInventoryItemData& item = InventoryComponent->GetItemAt(3);

	if (CurrentEquiped)
	{
		CurrentEquiped->Destroy();
	}



	// Spawn actor
	FActorSpawnParameters Params;
	Params.Owner = this;
	Params.Instigator = GetInstigator();
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	if (item.Quantity != 0)
	{
		auto spawn = GetWorld()->SpawnActor<APickupableItem>(item.ItemActorClass, this->GetTargetLocation(), FRotator::ZeroRotator, Params);
		spawn->AttachToComponent(AttachPoint, FAttachmentTransformRules::SnapToTargetIncludingScale, FName("NONE"));
		FQuat quat(FRotator(172.799545, 104.399696, 0.0));

		spawn->SetActorRelativeRotation(quat);
		spawn->SetItemState(EItemState::EIS_Equipped);
		CurrentEquiped = spawn;
		CurrentSlot = 3;
	}


	
}

void AMainCharacter::Unequip()
{
	if (CurrentEquiped)
	{
		CurrentEquiped->Destroy();
	}



}

void AMainCharacter::Shift()
{
	if (bShift)
	{
		bShift = false;
		GetCharacterMovement()->MaxWalkSpeed = 300;

		return;
	}
	if (!bShift)
	{
		bShift = true;
		GetCharacterMovement()->MaxWalkSpeed = 600;
		return;
	}
	
	
}

void AMainCharacter::ScopeOn()
{

	

	if (CharacterInstance)
	{

		if (CharacterInstance->Aiming == true)
		{
			CharacterInstance->Aiming = false;
			UE_LOG(LogTemp, Warning, TEXT("  false"));
			return;
		}
		if (CharacterInstance->Aiming == false)
		{
			CharacterInstance->Aiming = true;
			UE_LOG(LogTemp, Warning, TEXT("  true"));
			return;
		}

	}
	if (CharacterInstance == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Null Ptr"));
	}
}

void AMainCharacter::Inventory()
{
	if (bInventoryIsOpen)
	{
		bInventoryIsOpen = false;
		if (MainPlayerController)
		{
			MainPlayerController->HideInventory();
			UE_LOG(LogTemp, Warning, TEXT("ClosedInventory"));
		}
		return;
	}
	if (!bInventoryIsOpen)
	{
		UE_LOG(LogTemp, Warning, TEXT("OpenInventory"));
		MainPlayerController->ShowInventory();
		bInventoryIsOpen = true;
		return;
	}



}


void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bInteractable) {
		CurrentTraceItem();
		if (CurrentItem != PreviousItem && PreviousItem)
		{
			PreviousItem->GetWidgetComponent()->SetVisibility(false);

			if(CurrentItem)
			CurrentItem->GetWidgetComponent()->SetVisibility(true);

			
		}
		PreviousItem = CurrentItem;
	}

}

void AMainCharacter::AddControllerYawInput(float Val)
{
	if (Val != 0.f && Controller && Controller->IsLocalPlayerController())
	{
		
		

		APlayerController* const PC = CastChecked<APlayerController>(Controller);
		PC->AddYawInput(Val);

		

	}
}






void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMainCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainCharacter::MoveRight);

	
	PlayerInputComponent->BindAxis("Turn", this, &AMainCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AMainCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AMainCharacter::LookUpAtRate);

	PlayerInputComponent->BindAction("Crouch",IE_Pressed,this, &AMainCharacter::Crouch);
	//PlayerInputComponent->BindAction("Crouch", IE_Released, this, &AMainCharacter::StopCrouch);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AMainCharacter::Fire);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &AMainCharacter::StopFire);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AMainCharacter::EPressed);
	PlayerInputComponent->BindAction("Interact", IE_Released, this, &AMainCharacter::EReleased);
	
	PlayerInputComponent->BindAction("Drop", IE_Pressed, this, &AMainCharacter::DropItem);

	PlayerInputComponent->BindAction("Slot-1",IE_Pressed, this, &AMainCharacter::Slot1);
	PlayerInputComponent->BindAction("Slot-2", IE_Pressed, this, &AMainCharacter::Slot2);
	PlayerInputComponent->BindAction("Slot-3", IE_Pressed, this, &AMainCharacter::Slot3);
	PlayerInputComponent->BindAction("Slot-4", IE_Pressed, this, &AMainCharacter::Slot4);
	PlayerInputComponent->BindAction("Unequip", IE_Pressed, this, &AMainCharacter::Unequip);
	PlayerInputComponent->BindAction("Shift", IE_Pressed, this, &AMainCharacter::Shift);
	PlayerInputComponent->BindAction("ScopeOn", IE_Pressed, this, &AMainCharacter::ScopeOn);
	PlayerInputComponent->BindAction("Inventory", IE_Pressed, this, &AMainCharacter::Inventory);
}
void AMainCharacter::CurrentTraceItem()
{
	FVector StartLoc = camera->GetComponentLocation();
	FVector ForwardLoc = camera->GetForwardVector();
	FVector EndLoc = StartLoc + ForwardLoc * 250;

	FHitResult HitResult;
	//UE_LOG(LogTemp, Warning, TEXT("RayCastProblem"));
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	
	
		GetWorld()->LineTraceSingleByChannel(
			HitResult,
			StartLoc,
			EndLoc,
			ECollisionChannel::ECC_Visibility);
		
	//	DrawDebugLine(GetWorld(), StartLoc, EndLoc, FColor::Red, false, 3.f);
		

	
		ABaseInteractable* Item = Cast<ABaseInteractable>(HitResult.Actor);

		APickupableItem* PickableItem = Cast<APickupableItem>(HitResult.Actor);





		if (HitResult.bBlockingHit && Item )
		{
			/*
			if (PickableItem)
			{
				GEngine->AddOnScreenDebugMessage(23, 4, FColor::Green, FString("Pickable Item Dectated"));
				PickupableItem = PickableItem;
				CurrentItem = Item;
				CurrentItem->GetWidgetComponent()->SetVisibility(true);
			}
		*/

			
			
			CurrentItem = PickableItem;
			
			if (!bIsReading)
			{
				CurrentItem->GetWidgetComponent()->SetVisibility(true);
			}
			GEngine->AddOnScreenDebugMessage(23, 4, FColor::Green, FString("Traceing Widget"));
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, FString::Printf(TEXT("Hit Actor: %s"), *HitResult.GetActor()->GetName()));
		}
			
		
		
		else 
		{
			GEngine->AddOnScreenDebugMessage(23, 4, FColor::Red, FString("Failed Traceing Widget"));
			CurrentItem = nullptr;
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("NOTHING HIT"));
			
		}
		
		
		
	
		
}


void AMainCharacter::Equip()
{
	



}

void AMainCharacter::PlayCameraShake(TSubclassOf<UCameraShakeBase> WeaponShake)
{
	MainPlayerController->ClientPlayCameraShake(WeaponShake);


}



void  AMainCharacter::Pickup()
{
	
	if (!CurrentItem)return;
	

	if (CurrentItem) 
	{
		CurrentItem->Interact(this);
		if (CurrentItem->IsPickable()==true)
		{
			
			InventoryComponent->AddItem(CurrentItem->ItemData);
			
			CurrentItem = nullptr;
		
			
		
			UE_LOG(LogTemp, Error, TEXT("-------------------------------------------------"));



		}
	}
	
}

void AMainCharacter::TakeHealth(float value)
{
	Health -= value;
	Health = FMath::Clamp(Health, 0.0f, 100.f);
	float percentage = Health / 100.f;
	AMainCharacterController* Charactercontroller = Cast<AMainCharacterController>(Controller);


	Charactercontroller->UpdateHealth(percentage);

}

void AMainCharacter::TakeStamina(float value)
{
	Stamina -= value;
	Stamina = FMath::Clamp(Stamina, 0.f, 100.f);
	float Percentage = Stamina / 100;
	AMainCharacterController* Charactercontroller = Cast<AMainCharacterController>(Controller);
	
	Charactercontroller->UpdateStamina(Percentage);

}

void AMainCharacter::TakeRadioactive(float value)
{
	Radioactive -= value;
	Radioactive = FMath::Clamp(Radioactive, 0.f, 100.f);
	float Percentage = Radioactive / 100.f;
	AMainCharacterController* Charactercontroller = Cast<AMainCharacterController>(Controller);
	Charactercontroller->UpdateRadioactive(Percentage);


}

void AMainCharacter::UpdateHungerAndThirst()
{
	Hunger = FMath::Clamp(Hunger, 0.0f, 100.f);
	Thirst = FMath::Clamp(Thirst, 0.0f, 100.0f);

	if (Hunger <= 0 || Thirst <= 0)
	{

		TakeHealth(1.5f);
	}
	AMainCharacterController* Charactercontroller = Cast<AMainCharacterController>(Controller);
	float HungerPercentage = Hunger / 100.f;
	float ThirstPercentage = Thirst / 100.f;

	Charactercontroller->UpdateHungerAndThirst(HungerPercentage, ThirstPercentage);
	


}

void AMainCharacter::EquipFromIndex(int32 index)
{
	if (bIsReading)return;
	

		UE_LOG(LogTemp, Warning, TEXT("Slot1 is pressed!"));


		const	FInventoryItemData& item = InventoryComponent->GetItemAt(index);
		if (item.Quantity == 0)return;

		/*if (CurrentEquiped->ItemData.ItemName == item.ItemName)
		{

			CurrentEquiped->Destroy();
			return;
		}*/

		// Spawn actor

		FActorSpawnParameters Params;
		Params.Owner = this;
		Params.Instigator = GetInstigator();
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	

		if (CurrentEquiped)
		{
			CurrentEquiped->Destroy();
		}


		if (item.Quantity != 0)
		{


			
			FName SocketName = item.SocketName;
			auto spawn = GetWorld()->SpawnActor<APickupableItem>(item.ItemActorClass, GetMesh()->GetSocketLocation(SocketName), GetMesh()->GetSocketRotation(SocketName), Params);
			spawn->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName(SocketName));
			

			spawn->SetItemState(EItemState::EIS_Equipped);
			CurrentEquiped = spawn;
			CurrentSlot = 0;


			if (CurrentEquiped)
			{
				//CurrentWeaponType=CurrentEquiped
				UE_LOG(LogTemp, Warning, TEXT("Magic is happenigng!"));
				//CurrentWeaponType=CurrentEquiped->GetWeaponType()
				CurrentWeaponType = CurrentEquiped->ItemType;

				//FVector Loc= CurrentWeapon->GetWeaponMesh()->GetSocketLocation(CurrentWeapon->SlotName);
				//FRotator Roc = CurrentWeapon->GetWeaponMesh()->GetSocketRotation(CurrentWeapon->SlotName);
				CurrentEquiped->ItemData.IdCode = InventoryComponent->slot[index].IdCode;
			}





		}

	
}

void AMainCharacter::DropFromIndex(int32 index)
{
	if (bIsReading)
	{
		return;
	}

	if (!InventoryComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("DropFromIndex: InventoryComponent is NULL"));
		return;
	}
	if (!InventoryComponent->IsValidIndex(index))
	{
		UE_LOG(LogTemp, Warning, TEXT("DropFromIndex: Invalid index %d"), index);

		return;
	}




		const FInventoryItemData& Item = InventoryComponent->GetItemAt(index);
		
		if (Item.ItemActorClass == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("DropFromIndex: Invalid index %d"));
			return;
		}



		if (CurrentEquiped)
		{
			if (Item.ItemName == CurrentEquiped->ItemData.ItemName)
			{
				//CurrentEquiped->Destroy();
				/*
				CurrentEquiped->GetMesh()->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
				CurrentEquiped->GetSkeletalMesh()->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
				CurrentEquiped->SetItemState(EItemState::EIS_Falling);
				InventoryComponent->RemoveItem(Item);
				
				CurrentWeaponType = EItemType::None;

				////////////////////////////////////*                             ///////////////////*/
				CurrentEquiped->Destroy();
				
				FActorSpawnParameters SpawnParams;
				SpawnParams.Instigator = GetInstigator();
				SpawnParams.Owner = this;
				SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

				FVector Loc = GetActorLocation() + GetActorForwardVector() * 100.f;
				Loc.Z -= 250.f;
				FRotator Rot = GetActorRotation();

				InventoryComponent->RemoveItem(Item);

				CurrentWeaponType = EItemType::None;


				auto Spawn = GetWorld()->SpawnActor<APickupableItem>(Item.ItemActorClass, Loc, Rot, SpawnParams);

				Spawn->SetItemState(EItemState::EIS_Falling);

				return;
			}
		}
		FActorSpawnParameters SpawnParams;
		SpawnParams.Instigator = GetInstigator();
		SpawnParams.Owner = this;
		SpawnParams.SpawnCollisionHandlingOverride=ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		FVector Loc = GetActorLocation() + GetActorForwardVector()*100.f;
		Loc.Z -= 250.f;
		FRotator Rot = GetActorRotation();


		

		auto Spawn = GetWorld()->SpawnActor<APickupableItem>(Item.ItemActorClass, Loc, Rot, SpawnParams);
		
		Spawn->SetItemState(EItemState::EIS_Falling);
		InventoryComponent->RemoveItem(Item);
	


	



}

void AMainCharacter::EPressed()
{
	
	bEPressed = true;
	if (CurrentItem)
		Pickup();
		
}

void AMainCharacter::EReleased()
{
	bEPressed = false;
	




}