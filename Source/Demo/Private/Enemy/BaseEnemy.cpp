// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/BaseEnemy.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "DrawDebugHelpers.h"
#include "Demo/Public/character/MainCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/WidgetComponent.h"
// Sets default values
ABaseEnemy::ABaseEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PERCEPTION"));
	
	bAttackable = false;
	
	AIConfig=CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("AICONFIG"));
	AIConfig->SightRadius = 1500.f;
	AIConfig->LoseSightRadius = 1800.f;
	//AIConfig->bDebugEnabled = true; // VERY important

	AIConfig->PeripheralVisionAngleDegrees = 90.f;
	AIConfig->DetectionByAffiliation.bDetectEnemies = true;
	AIConfig->DetectionByAffiliation.bDetectFriendlies = true;
	AIConfig->DetectionByAffiliation.bDetectNeutrals = true;
	

	PerceptionComponent->ConfigureSense(*AIConfig);
	PerceptionComponent->SetDominantSense(*AIConfig->GetSenseImplementation());
	PerceptionComponent->bEditableWhenInherited = true;

	PerceptionStimuliSourceComponent = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("StimuliSourceComp"));

	PerceptionStimuliSourceComponent->RegisterWithPerceptionSystem();
	
	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBar"));
	WidgetComponent->SetupAttachment(GetRootComponent());

	WidgetComponent->SetVisibility(false);

	

	bAttacking = false;
	bAttackable = false;
	EEnenmyState::IDLE;
}

// Called when the game starts or when spawned
void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();

  PerceptionComponent->OnPerceptionUpdated.AddDynamic(this, &ABaseEnemy::OnPerceptionUpdate);


  EnemyController = Cast<AAIController>(GetController());

  if (EnemyController)
  {
	  BlackBoardComponent = EnemyController->GetBlackboardComponent();
  }
	

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

void ABaseEnemy::Chase()
{
	if (!TargetPawn)return;

	WidgetComponent->SetVisibility(true);
	AAIController* AI = Cast<AAIController>(GetController());
	if (AI)
	{
		AI->MoveToActor(TargetPawn, 100.f);
		bAttacking = false;
		bAttackable = false;
		
	}

//	GetWorldTimerManager().SetTimer(DistanceTime, this, &ABaseEnemy::CheckDistanceToPlayer, 1.f, true, 0.2f);
	


}

void ABaseEnemy::Flee(ACharacter* Character)
{
}

void ABaseEnemy::Attack()
{
	bAttacking = true;
	UE_LOG(LogTemp, Error, TEXT("Attack"));


}

void ABaseEnemy::CheckDistanceToPlayer()
{
	FVector MyLoc = GetActorLocation();
	FVector PlayerLoc = TargetPawn->GetActorLocation();

	// Ignore vertical difference if you only care about 2D distance
	MyLoc.Z = 0;
	PlayerLoc.Z = 0;

	float Distance = FVector::DistSquaredXY(MyLoc, PlayerLoc);

	if (Distance <= 90000.f)
	{
		UE_LOG(LogTemp, Warning, TEXT("Attabke now attack"));
		
		bAttackable = true;
		BlackBoardComponent->SetValueAsBool(TEXT("IsInRange"), bAttackable);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Chase Again"));
		UE_LOG(LogTemp, Error, TEXT("Distance: %f"),Distance);
		//Chase(TargetPawn);
		bAttackable = false;
		bAttacking = false;
	}




}

void ABaseEnemy::OnPerceptionUpdate(const TArray<AActor*>& UpdatedActors)
{
	AMainCharacter* PlayerCharacter = Cast<AMainCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));

	for (AActor* Actor : UpdatedActors)
	{
		if (Actor==PlayerCharacter )
		{
			DrawDebugLine(
				GetWorld(),
				GetActorLocation(),
				Actor->GetActorLocation(),
				FColor::Red,
				false,
				1.f,
				0,
				2.f
				
			);
			TargetPawn = PlayerCharacter;
			//Chase(PlayerCharacter);

			FString name;
			name = Actor->GetName();
			UE_LOG(LogTemp, Warning,TEXT("Name: %s"),*name);
			BlackBoardComponent->SetValueAsObject(TEXT("TargetActor"), TargetPawn);
			

		}
	}


}



