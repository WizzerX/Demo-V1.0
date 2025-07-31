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
#include "Demo/Item/Interactable.h"
#include "Components/WidgetComponent.h"
#include <Kismet/GameplayStatics.h>
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"

AMainCharacter::AMainCharacter()
{
 	
	PrimaryActorTick.bCanEverTick = true;
	springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	springArm->SetupAttachment(RootComponent);

	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	camera->SetupAttachment(springArm);

	AttachPoint = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	AttachPoint->AttachTo(GetRootComponent());
	
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

}


void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bInteractable) {
		CurrentTraceItem();
		if (CurrentItem != PreviousItem && PreviousItem)
		{

			PreviousItem->GetWidgetComponent()->SetVisibility(false);

			if (CurrentItem) {
				PreviousItem->GetWidgetComponent()->SetVisibility(true);
			}

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

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AMainCharacter::Pickup);
	


}
void AMainCharacter::CurrentTraceItem()
{
	FVector StartLoc = camera->GetComponentLocation();
	FVector ForwardLoc = camera->GetForwardVector();
	FVector EndLoc = StartLoc + ForwardLoc * 250;

	FHitResult HitResult;
	UE_LOG(LogTemp, Warning, TEXT("RayCastProblem"));
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	
	
		GetWorld()->LineTraceSingleByChannel(
			HitResult,
			StartLoc,
			EndLoc,
			ECollisionChannel::ECC_Visibility);
		
		DrawDebugLine(GetWorld(), StartLoc, EndLoc, FColor::Red, false, 3.f);
		GEngine->AddOnScreenDebugMessage(23, 4, FColor::Green, FString("Jak is jacking"));

		AInteractable* Item = Cast <AInteractable>(HitResult.Actor);
		
		
		if (HitResult.bBlockingHit && Item)
		{
			CurrentItem = Item;
			CurrentItem->GetWidgetComponent()->SetVisibility(true);
				
			
			

		}
		else {
			CurrentItem = nullptr;
		}
		
		
		
	
	
}


void AMainCharacter::Equip()
{
	



}

void  AMainCharacter::Pickup()
{
	if (!CurrentItem)return;

	AttachPoint->SetupAttachment(CurrentItem->GetMesh());
	// Optional: disable collision and physics
	CurrentItem->GetBox()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	CurrentItem->GetSphere()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	CurrentItem->GetMesh()->SetSimulatePhysics(false);

	// Hide the widget
	CurrentItem->GetWidgetComponent()->SetVisibility(false);
	

	
}

