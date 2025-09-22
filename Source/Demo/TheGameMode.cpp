// Fill out your copyright notice in the Description page of Project Settings.


#include "TheGameMode.h"
#include "Components/Widget.h"
#include "Blueprint/UserWidget.h"
#include "character/MainCharacterController.h"
#include "character/MainCharacter.h"
ATheGameMode::ATheGameMode()
{
	
		DefaultPawnClass = AMainCharacter::StaticClass();        // your character
		PlayerControllerClass = AMainCharacterController::StaticClass(); // your controller
		                 
	



}

void ATheGameMode::ChangeWidget(TSubclassOf<UUserWidget> NewWidget)
{
	if (CurrentWidget)
	{
		CurrentWidget->RemoveFromViewport();
		CurrentWidget = nullptr;
	}
	if (NewWidget)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidget);
		if (CurrentWidget)
		{
			CurrentWidget->AddToViewport();
		}



	}


}

void ATheGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	
	GEngine->AddOnScreenDebugMessage(2, 4, FColor::Green, FString("THE GAME MODE BEGIN PLAY"));


}
