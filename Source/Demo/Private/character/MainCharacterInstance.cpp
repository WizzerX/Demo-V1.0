// Fill out your copyright notice in the Description page of Project Settings.


#include "character/MainCharacterInstance.h"
#include  "character/MainCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Pawn.h"



void UMainCharacterInstance::NativeInitializeAnimation()
{
	
	MainCharacter = Cast<AMainCharacter>(TryGetPawnOwner());
	if (MainCharacter == nullptr) {
		UE_LOG(LogTemp,Error, TEXT("Error in getting the character!"));
	}

	UE_LOG(LogTemp, Error, TEXT("Instace class is Runing!"));

	
	

}


void UMainCharacterInstance::UpdateAnimationProperties(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);
	


	if (MainCharacter)
	{

		FVector Velocity{ MainCharacter->GetVelocity() };
		Velocity.Z = 0;
		speed = Velocity.Size();

		//UE_LOG(LogTemp, Warning, TEXT("Character: %s, Speed: %f"), *MainCharacter->GetName(), speed);

		bIsInAir = MainCharacter->GetCharacterMovement()->IsFalling();

		if (MainCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0)
		{
			bAccelerating = true;
		}
		else {
			bAccelerating = false;
		}


		if (TryGetPawnOwner())
		{
			
		}
		else
		{
			



		}





	}
}

