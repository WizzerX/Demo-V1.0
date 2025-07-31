// Fill out your copyright notice in the Description page of Project Settings.


#include "Demo/Item/Interactable.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include  "Demo/Charcter/MainCharacter.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AInteractable::AInteractable()
{
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	
	BoxMesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));

	BoxMesh->AttachTo(GetRootComponent());
	BoxComponent->SetupAttachment(SceneRoot);
	SphereComponent->SetupAttachment(SceneRoot);

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	WidgetComponent->SetupAttachment(GetRootComponent());
	SphereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	BoxComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	BoxComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, 
		ECollisionResponse::ECR_Block);
	WidgetComponent->SetVisibility(false);
	WidgetComponent->SetHiddenInGame(false);

	

}


void AInteractable::BeginPlay()
{
	Super::BeginPlay();


	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AInteractable::OnBoxBeginOverlap);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &AInteractable::OnBoxEndOverlap);
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AInteractable::OnSphereBeginOverlap);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &AInteractable::OnSphereEndOverlap);
	 CharacterRef = Cast<AMainCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

void AInteractable::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (OtherActor && OtherActor != this)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Begin Overlap!"));
		
		


	}

}

void AInteractable::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor != this)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("End Overlap!"));
		
	}


}

void AInteractable::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMainCharacter* Character=Cast<AMainCharacter>(OtherActor);
	if (OtherActor==Character && OtherActor != this)
	{
		CharacterRef->bInteractable = true;

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Player Dectaced Overlap!"));

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Sphere begin Overlap!"));


	}





}

void AInteractable::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AMainCharacter* Character = Cast<AMainCharacter>(OtherActor);
	if (OtherActor==Character && OtherActor != this)
	{
		CharacterRef->bInteractable = false;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Player END Dectaced Overlap!"));

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Sphere End Overlap!"));

	}



}

void AInteractable::Tick(float deltatime)
{




	

}



