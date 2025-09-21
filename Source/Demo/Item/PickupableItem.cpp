#include "Demo/Item/PickupableItem.h"
#include "Demo/Charcter/MainCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/BoxComponent.h"
#include "Demo/Item/BaseInteractable.h"
#include "Demo/Charcter/MainCharacter.h"
#include "Demo/Item/InventoryComponent.h"
APickupableItem::APickupableItem()
{


	WidgetComponent->SetVisibility(false);
	ItemState = EItemState::EIS_Pickup;



}


void APickupableItem::OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!OtherActor || OtherActor == this || !OtherComp) return;


	if (ItemState == EItemState::EIS_Falling && OtherComp->GetCollisionObjectType() == ECC_WorldStatic)
	{
		UE_LOG(LogTemp, Warning, TEXT("Item Landed, switching to Pickup"));
		SetItemState(EItemState::EIS_Pickup);
	}


}

void APickupableItem::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
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

void APickupableItem::SetItemProperties(EItemState State)
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
		BoxMesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
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



void APickupableItem::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMainCharacter* Character = Cast<AMainCharacter>(OtherActor);
	if (OtherActor == Character && OtherActor != this)
	{
		WidgetComponent->SetVisibility(false);
		CharacterRef->bInteractable = true;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Player END Dectaced Overlap!"));

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Sphere End Overlap!"));

	}

}

void APickupableItem::BeginPlay()
{
	Super::BeginPlay();
	BoxMesh->SetNotifyRigidBodyCollision(true);
	BoxMesh->OnComponentHit.AddDynamic(this, &APickupableItem::OnCompHit);
	CharacterRef = Cast<AMainCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
	




}

void APickupableItem::Interact(AMainCharacter* Character)
{
	GEngine->AddOnScreenDebugMessage(23, 4, FColor::Purple, FString("PURE FUNCTION IS CALLED"));
	

	
}



void APickupableItem::SetItemState(EItemState State)
{
	ItemState = State;
	SetItemProperties(State);

}


