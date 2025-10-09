// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/StoryItem/Notes.h"
#include "character/MainCharacter.h"
#include "Components/Widget.h"
#include "Item/Interactable/BaseInteractable.h"
#include "Demo/TheGameMode.h"
#include "Components/WidgetComponent.h"
#include "character/MainCharacterController.h"
#include "Kismet/GameplayStatics.h"
ANotes::ANotes()
{
	



}
			
void ANotes::Interact(AMainCharacter* Character)
{
	

	

	AMainCharacterController* CharacterController = Cast<AMainCharacterController>
		(Character->Controller);
	if (CharacterController && Character->bIsReading==false)
	{
		UGameplayStatics::PlaySound2D(GetWorld(),PageSound);
		NoteWidget = CreateWidget<UUserWidget>(GetWorld(), NoteWidgetClass);
		NoteWidget->AddToViewport();
		CharacterController->PlayerReadingNote(NoteWidget);
		Character->bIsReading = true;
		
		UE_LOG(LogTemp, Warning, TEXT("Player is Reading!"));
		UE_LOG(LogTemp, Warning, TEXT("bIsReading = %s"), Character->bIsReading ? TEXT("true") : TEXT("false"));
	
		
		
		
	}
	else if (CharacterController && Character->bIsReading == true)
	{
		CharacterController->PlayerStopReading(NoteWidget);
		Character->bIsReading = false;
		UE_LOG(LogTemp, Warning, TEXT("Stop reading!"));
		UE_LOG(LogTemp, Warning, TEXT("bIsReading = %s"), Character->bIsReading ? TEXT("true") : TEXT("false"));
		
	}

	


}

