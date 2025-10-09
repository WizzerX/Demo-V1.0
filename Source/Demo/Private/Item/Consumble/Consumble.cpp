// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Consumble/Consumble.h"




void AConsumble::Interact(AMainCharacter* Character)
{
	UE_LOG(LogTemp, Error, TEXT("APPLE IS USED!"));
}

AConsumble::AConsumble()
{
	

	UE_LOG(LogTemp, Error, TEXT("APPLE IS USED!"));



}

void AConsumble::UseConsumble()
{
	switch (ConsumbleType)
	{
	case EConsumbleType::Thirst:
		
		break;
	case EConsumbleType::Hunger:
		break;
	case EConsumbleType::RadioActiveHeal:
		break;
	case EConsumbleType::HealthHeal:
		break;
	case EConsumbleType::custom:
		break;
	default:
		break;
	}


}


	

