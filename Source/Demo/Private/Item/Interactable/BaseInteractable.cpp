	// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Interactable/BaseInteractable.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include  "character/MainCharacter.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"


ABaseInteractable::ABaseInteractable()
{
 	
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SetRootComponent(SceneComponent);

	SceneComponent->SetRelativeLocation(FVector(50.f, 0.0, 0.0));


	BoxMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	BoxMesh->SetupAttachment(SceneComponent);
	BoxMesh->SetVisibility(true);

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxComponent->SetupAttachment(BoxMesh);

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	SphereComponent->SetupAttachment(BoxMesh);




	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	WidgetComponent->SetVisibility(false);
	WidgetComponent->SetupAttachment(BoxMesh);


	
	ItemCategory = EItemCategory::IC_NONE;



}

void ABaseInteractable::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (OtherActor && OtherActor != this)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Begin Overlap!"));




	}




}

void ABaseInteractable::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

	

	if (OtherActor && OtherActor != this)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("End Overlap!"));

	}

}


void ABaseInteractable::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

	AMainCharacter* Character = Cast<AMainCharacter>(OtherActor);
	if (OtherActor == Character && OtherActor != this)
	{
		WidgetComponent->SetVisibility(false);
		CharacterRef->bInteractable = false;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Player END Dectaced Overlap!"));

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Sphere End Overlap!"));

	}


}

void ABaseInteractable::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMainCharacter* Character = Cast<AMainCharacter>(OtherActor);
	if (OtherActor == Character && OtherActor != this)
	{
		CharacterRef->bInteractable = true;

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Player Dectaced Overlap!"));

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Sphere begin Overlap!"));


	}


}


void ABaseInteractable::BeginPlay()
{
	Super::BeginPlay();


	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ABaseInteractable::OnBoxBeginOverlap);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &ABaseInteractable::OnBoxEndOverlap);
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ABaseInteractable::OnSphereBeginOverlap);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &ABaseInteractable::OnSphereEndOverlap);
	CharacterRef = Cast<AMainCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	
}

void ABaseInteractable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);






}

