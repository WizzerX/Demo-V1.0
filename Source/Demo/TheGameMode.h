// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TheGameMode.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_API ATheGameMode : public AGameModeBase
{
	GENERATED_BODY()


public:
	ATheGameMode();
	
	UFUNCTION(BlueprintCallable, Category = "ui")
	void ChangeWidget(TSubclassOf<UUserWidget>NewWidget);

protected:

	virtual void BeginPlay() override;

	UPROPERTY()
	UUserWidget* CurrentWidget;

	UPROPERTY(EditAnyWhere,BlueprintReadWrite,Category="ui")
	TSubclassOf<UUserWidget> StartingWidget;


};
