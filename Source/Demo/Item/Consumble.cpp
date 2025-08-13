// Fill out your copyright notice in the Description page of Project Settings.


#include "Demo/Item/Consumble.h"

void AConsumble::Interact(AMainCharacter* Character)
{
	GEngine->AddOnScreenDebugMessage(23, 4, FColor::Red, FString("USING APPLE"));
	UE_LOG(LogTemp, Error, TEXT("APPLE IS USED!"));


}

AConsumble::AConsumble()
{
	
	GEngine->AddOnScreenDebugMessage(23, 4, FColor::Red, FString("USING APPLE"));
	UE_LOG(LogTemp, Error, TEXT("APPLE IS USED!"));



}



	

