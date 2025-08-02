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

void AInteractable::SetItemState(EItemState State)
{
	ItemState = State;
	SetItemProperties(State);



}

void AInteractable::SetItemProperties(EItemState State)
{
	switch (State) 
	{
	case EItemState::EIS_Pickup:
		BoxMesh->SetVisibility(true);
		BoxMesh->SetSimulatePhysics(false);
		BoxMesh->SetEnableGravity(false);
		BoxMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
		BoxMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		SphereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

		BoxComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
		BoxComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility,
			ECollisionResponse::ECR_Block);
		break;
	case EItemState::EIS_EquipInterping:
		BoxMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		BoxMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

		SphereComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		SphereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

		BoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		BoxComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

		BoxMesh->SetSimulatePhysics(false);
		BoxMesh->SetEnableGravity(false);
		BoxMesh->SetVisibility(true);
		break;
	case EItemState::EIS_PickedUp:
		BoxMesh->SetVisibility(false);
		BoxMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		BoxMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

		SphereComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		SphereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

		BoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		BoxComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

		BoxMesh->SetSimulatePhysics(false);
		BoxMesh->SetEnableGravity(false);
		break;
	case EItemState::EIS_Equipped:
		BoxMesh->SetVisibility(true);
		BoxMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		BoxMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

		SphereComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		SphereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

		BoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		BoxComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

		BoxMesh->SetSimulatePhysics(false);
		BoxMesh->SetEnableGravity(false);
		break;
	case EItemState::EIS_Falling:
		BoxMesh->SetVisibility(true);
		BoxMesh->SetEnableGravity(true);
		BoxMesh->SetSimulatePhysics(true);

		BoxMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
		BoxMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Block);

		BoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		BoxComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

		SphereComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		SphereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

		break;




	}




}



