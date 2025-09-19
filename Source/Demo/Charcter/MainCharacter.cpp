// Fill out your copyright notice in the Description page of Project Settings.


#include "Demo/Charcter/MainCharacter.h"
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
#include "Demo/Item/PickupableItem.h"
#include "Demo/Item/InventoryComponent.h"
#include "string"
#include "Components/Widget.h"
#include "Widget/MainWidget.h"
#include "Widget/QuickSlotBarWidget.h"
#include "Demo/Charcter/MainCharacterController.h"
AMainCharacter::AMainCharacter()
{
 	
	PrimaryActorTick.bCanEverTick = true;
	springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	springArm->SetupAttachment(RootComponent);

	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	camera->SetupAttachment(springArm);

	AttachPoint = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	AttachPoint->AttachTo(GetRootComponent());
	
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));
	
	
}


void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	
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
	bCrouch = true;
	UE_LOG(LogTemp, Warning, TEXT("Crouching"));
	
	
	GetCapsuleComponent()->SetCapsuleHalfHeight(44);
	float CapsuleHeight = GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight();

	UE_LOG(LogTemp, Warning, TEXT("Capsule Half Height: %f"), CapsuleHeight);
	
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("c"));


}

void AMainCharacter::StopCrouch()
{
	bCrouch = false;
	GetCapsuleComponent()->SetCapsuleHalfHeight(88);
	UE_LOG(LogTemp, Warning, TEXT("Stop_Crouching"));

}

void AMainCharacter::Fire()
{
	FVector StartLoc = camera->GetComponentLocation();
	FVector ForwardLoc = camera->GetForwardVector();
	FVector EndLoc = StartLoc + ForwardLoc *800;

	FHitResult HitResult;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	

	GetWorld()->LineTraceSingleByChannel(HitResult, StartLoc, EndLoc, ECollisionChannel::ECC_WorldStatic, Params);

	DrawDebugLine(GetWorld(), StartLoc, EndLoc, FColor::Red, false, 5.f);
	/*
	if (CurrentItem)
	{
		CurrentItem->SetItemState(EItemState::EIS_Pickup);
		
	}
	
	*/
}

void AMainCharacter::DropItem()
{
	
	if (!CurrentItem )return;

	
	UE_LOG(LogTemp, Warning, TEXT("Drop THE ITEM"));
	
	if (CurrentItem)
	{
		CurrentItem->GetMesh()->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);




		CurrentItem->SetItemState(EItemState::EIS_Falling);

		
		PickupableItem = nullptr;
		CurrentItem = nullptr;
		PreviousItem = nullptr;
	}
	

}

void AMainCharacter::Slot1()
{
	UE_LOG(LogTemp, Warning, TEXT("Slot1 is pressed!"));

	
		const	FInventoryItemData& item = InventoryComponent->GetItemAt(0);


		// Spawn actor
		FActorSpawnParameters Params;
		Params.Owner = this;
		Params.Instigator = GetInstigator();
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		GetWorld()->SpawnActor<APickupableItem>(item.ItemActorClass, this->GetTargetLocation(), FRotator::ZeroRotator, Params);
		InventoryComponent->RemoveItem(item);
	



	

}

void AMainCharacter::Slot2()
{
	UE_LOG(LogTemp, Warning, TEXT("Slot2  is pressed!"));
const FInventoryItemData& item = InventoryComponent->GetItemAt(1);


	// Spawn actor
	FActorSpawnParameters Params;
	Params.Owner = this;
	Params.Instigator = GetInstigator();
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	GetWorld()->SpawnActor<APickupableItem>(item.ItemActorClass, this->GetTargetLocation(), FRotator::ZeroRotator, Params);
	InventoryComponent->RemoveItem(item);



}

void AMainCharacter::Slot3()
{
	UE_LOG(LogTemp, Warning, TEXT("Slot3  is pressed!"));
	const FInventoryItemData& item = InventoryComponent->GetItemAt(2);

	// Spawn actor
	FActorSpawnParameters Params;
	Params.Owner = this;
	Params.Instigator = GetInstigator();
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	GetWorld()->SpawnActor<APickupableItem>(item.ItemActorClass, this->GetTargetLocation(), FRotator::ZeroRotator, Params);
	InventoryComponent->RemoveItem(item);


}

void AMainCharacter::Slot4()
{
	UE_LOG(LogTemp, Warning, TEXT("Slot4  is pressed!"));
	const FInventoryItemData& item = InventoryComponent->GetItemAt(3);

	// Spawn actor
	FActorSpawnParameters Params;
	Params.Owner = this;
	Params.Instigator = GetInstigator();
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	GetWorld()->SpawnActor<APickupableItem>(item.ItemActorClass, this->GetTargetLocation(), FRotator::ZeroRotator, Params);
	InventoryComponent->RemoveItem(item);


	
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


void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMainCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainCharacter::MoveRight);

	
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AMainCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AMainCharacter::LookUpAtRate);

	PlayerInputComponent->BindAction("Crouch",IE_Pressed,this, &AMainCharacter::Crouch);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &AMainCharacter::StopCrouch);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AMainCharacter::Fire);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AMainCharacter::EPressed);
	PlayerInputComponent->BindAction("Interact", IE_Released, this, &AMainCharacter::EReleased);
	
	PlayerInputComponent->BindAction("Drop", IE_Pressed, this, &AMainCharacter::DropItem);

	PlayerInputComponent->BindAction("Slot-1",IE_Pressed, this, &AMainCharacter::Slot1);
	PlayerInputComponent->BindAction("Slot-2", IE_Pressed, this, &AMainCharacter::Slot2);
	PlayerInputComponent->BindAction("Slot-3", IE_Pressed, this, &AMainCharacter::Slot3);
	PlayerInputComponent->BindAction("Slot-4", IE_Pressed, this, &AMainCharacter::Slot4);
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
		
		DrawDebugLine(GetWorld(), StartLoc, EndLoc, FColor::Red, false, 3.f);
		

	
		ABaseInteractable* Item = Cast<ABaseInteractable>(HitResult.Actor);

		APickupableItem* PickableItem = Cast<APickupableItem>(HitResult.Actor);





		if (HitResult.bBlockingHit && Item)
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
			
			CurrentItem->GetWidgetComponent()->SetVisibility(true);
				
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

void  AMainCharacter::Pickup()
{
	
	if (!CurrentItem)return;
	

	if (CurrentItem) 
	{
		CurrentItem->Interact(this);
		if (CurrentItem->IsPickable())
		{
			
			InventoryComponent->AddItem(CurrentItem->ItemData);
			
			AMainCharacterController* MyPC = Cast<AMainCharacterController>(GetController());

			UMainWidget* Widget = Cast<UMainWidget>(MyPC->SlotWidget);
			if (Widget)
			{
				
				//Widget->QuickSlotBar->SlotWidgetDelegate.Broadcast(InventoryComponent->GetIndex(), CurrentItem->ItemData);
				Widget->QuickSlotBar->TestDelegate.Broadcast(50);
				size_t g = InventoryComponent->GetIndex();
				InventoryComponent->SlotWidgetDelegate.Broadcast(InventoryComponent->GetIndex(), CurrentItem->ItemData);
				UE_LOG(LogTemp, Warning, TEXT("Inventorycomponent INDEX %d"), g);
				//Widget->UpdateUIAt(0,CurrentItem->ItemData.Icon, CurrentItem->ItemData.Quantity);
				UE_LOG(LogTemp, Error, TEXT("Widget Scucess"));

			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Cast Failed!"));
			}


			CurrentItem->Destroy();
			



		}
	}
	
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