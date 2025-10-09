// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/BaseEnemy.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AIPerceptionTypes.h"

// Sets default values
ABaseEnemy::ABaseEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PERCEPTION"));
	PerceptionStimuliSourceComponent = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("PerceptionStimuli"));
	
	
	AIConfig=CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("AICONFIG"));
	AIConfig->SightRadius = 1500.f;
	AIConfig->LoseSightRadius = 1800.f;
	AIConfig->PeripheralVisionAngleDegrees = 90.f;
	AIConfig->DetectionByAffiliation.bDetectEnemies = true;
	AIConfig->DetectionByAffiliation.bDetectFriendlies = true;
	AIConfig->DetectionByAffiliation.bDetectNeutrals = true;
	
	


	PerceptionComponent->ConfigureSense(*AIConfig);
	PerceptionComponent->SetDominantSense(*AIConfig->GetSenseImplementation());
	PerceptionComponent->bEditableWhenInherited = true;
	
	PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ABaseEnemy::OnPerceptionUpdate);
	EEnenmyState::IDLE;
}

// Called when the game starts or when spawned
void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABaseEnemy::Roam()
{
}

void ABaseEnemy::Chase(ACharacter* Character)
{
}

void ABaseEnemy::Flee(ACharacter* Character)
{
}

void ABaseEnemy::Attack(ACharacter* Character)
{
}

void ABaseEnemy::OnPerceptionUpdate(AActor* Actor,const FAIStimulus& Stimulus)
{
	UE_LOG(LogTemp,Error, TEXT("AI IS WORKING!"));


}

