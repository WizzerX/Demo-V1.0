// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainCharacterController.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_API AMainCharacterController : public APlayerController
{
	GENERATED_BODY()


protected:
	
	virtual void BeginPlay() override;



public:
	AMainCharacterController();



	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> QuickSlotClass;

class	UMainWidget* MainWidget;

void PlayerReadingNote(UUserWidget* mywidget);
void PlayerStopReading(UUserWidget* widget);

void UpdateHealth(float value);
void UpdateStamina(float value);
void UpdateHunger(float value);
void UpdateRadioactive(float value);
void UpdateThirst(float value);
};
