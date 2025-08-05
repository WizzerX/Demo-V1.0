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
	
	
	


	BoxMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(BoxMesh);


	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxComponent->SetupAttachment(BoxMesh);
	
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	SphereComponent->SetupAttachment(GetRootComponent());
	

	
	
	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	WidgetComponent->SetVisibility(false);
	WidgetComponent->SetupAttachment(GetRootComponent());
	

	ItemState = EItemState::EIS_Pickup;
	
	

}


void AInteractable::BeginPlay()
{
	Super::BeginPlay();

	BoxMesh->OnComponentHit.AddDynamic(this, &AInteractable::OnCompHit);
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AInteractable::OnBoxBeginOverlap);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &AInteractable::OnBoxEndOverlap);
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AInteractable::OnSphereBeginOverlap);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &AInteractable::OnSphereEndOverlap);
	 CharacterRef = Cast<AMainCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	 BoxMesh->SetNotifyRigidBodyCollision(true);
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
		WidgetComponent->SetVisibility(false);
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



void AInteractable::OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
	FVector NormalImpulse, const FHitResult& Hit)
{

	
	if (!OtherActor || OtherActor == this || !OtherComp) return;


	if (ItemState == EItemState::EIS_Falling && OtherComp->GetCollisionObjectType() == ECC_WorldStatic)
	{
		UE_LOG(LogTemp, Warning, TEXT("Item Landed, switching to Pickup"));
		// ?? FIRST: Stop physics immediately
		//BoxMesh->SetSimulatePhysics(false);
//		BoxMesh->SetEnableGravity(false);

		SetItemState(EItemState::EIS_Pickup);
	}

	


}

void AInteractable::CheckIfLanded()
{

	FVector Start = GetActorLocation();
	FVector End = Start - FVector(0, 0, 10); // small downward trace
	FHitResult Hit;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_WorldStatic, Params);
	
	if (bHit && BoxMesh->IsSimulatingPhysics() && BoxMesh->GetPhysicsLinearVelocity().Size() < 10.f)
	{
		UE_LOG(LogTemp, Warning, TEXT("LineTraceing is Happening"));
		SetItemState(EItemState::EIS_Pickup);
	}
}

void AInteractable::SetItemProperties(EItemState State)
{
	switch (State) 
	{
	case EItemState::EIS_Pickup:
	
		BoxMesh->SetSimulatePhysics(false);
		BoxMesh->SetEnableGravity(false);
		BoxMesh->SetVisibility(true);
		BoxMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		BoxMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

		SphereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
		SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);


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
		WidgetComponent->SetVisibility(false);
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
		WidgetComponent->SetVisibility(false);
		
		break;
	case EItemState::EIS_Falling:
		BoxMesh->SetVisibility(true);
		BoxMesh->SetEnableGravity(true);
		BoxMesh->SetSimulatePhysics(true);
		BoxMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		BoxMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
		BoxMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Block);
		BoxMesh->SetCollisionObjectType(ECC_PhysicsBody);


		BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		BoxComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

		SphereComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		SphereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
		break;




	}




}



