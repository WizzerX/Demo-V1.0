#include "Item/Interactable/PickupableItem.h"
#include "character/MainCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/BoxComponent.h"
#include "Item/Interactable/BaseInteractable.h"
#include "character/MainCharacter.h"
#include "Item/Inventory/InventoryComponent.h"
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
		// ===================== PICKUP (ON GROUND, INTERACTABLE) =====================
	case EItemState::EIS_Pickup:
	{
		// World mesh visible
		BoxMesh->SetVisibility(true);
		BoxMesh->SetSimulatePhysics(true);
		BoxMesh->SetEnableGravity(true);

		BoxMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		BoxMesh->SetCollisionObjectType(ECC_WorldDynamic);
		BoxMesh->SetCollisionResponseToAllChannels(ECR_Block);

		// Weapon mesh hidden (not equipped yet)
		WeaponMesh->SetVisibility(false);
		WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		// Interaction sphere ON
		SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		SphereComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
		SphereComponent->SetGenerateOverlapEvents(true);

		// Extra collision OFF
		BoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		// UI hidden until player enters sphere
		WidgetComponent->SetVisibility(false);
		break;
	}

	// ===================== FALLING / DROPPED =====================
	case EItemState::EIS_Falling:
	{
		BoxMesh->SetVisibility(true);
		BoxMesh->SetSimulatePhysics(true);
		BoxMesh->SetEnableGravity(true);
		BoxMesh->WakeAllRigidBodies();

		BoxMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		BoxMesh->SetCollisionObjectType(ECC_PhysicsBody);
		BoxMesh->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
		BoxMesh->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
		BoxMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);

		WeaponMesh->SetVisibility(false);
		WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
		SphereComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		SphereComponent->SetGenerateOverlapEvents(false);

		BoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		BoxComponent->SetGenerateOverlapEvents(false);
		WidgetComponent->SetVisibility(false);
		break;
	}

	// ===================== EQUIP INTERPING (ANIMATING TO HAND) =====================
	case EItemState::EIS_EquipInterping:
	{
		BoxMesh->SetVisibility(false);
		BoxMesh->SetSimulatePhysics(false);
		BoxMesh->SetEnableGravity(false);
		BoxMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		WeaponMesh->SetVisibility(true);
		WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		SphereComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		BoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		WidgetComponent->SetVisibility(false);
		break;
	}

	// ===================== EQUIPPED (IN HAND) =====================
	case EItemState::EIS_Equipped:
	{



		// World mesh OFF
		BoxMesh->SetVisibility(false);
		BoxMesh->SetSimulatePhysics(false);
		BoxMesh->SetEnableGravity(false);
		BoxMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		// Weapon mesh ON
		WeaponMesh->SetVisibility(true);
		WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		// No interaction while equipped
		SphereComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		BoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		WidgetComponent->SetVisibility(false);

	




		break;
	}

	// ===================== PICKED UP (IN INVENTORY, NOT EQUIPPED) =====================
	case EItemState::EIS_PickedUp:
	{
		BoxMesh->SetVisibility(false);
		BoxMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		BoxMesh->SetSimulatePhysics(false);
		BoxMesh->SetEnableGravity(false);

		WeaponMesh->SetVisibility(false);
		WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		SphereComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		BoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		WidgetComponent->SetVisibility(false);
		break;
	}

	default:
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

	//ItemData.IdCode = FGuid::NewGuid();

	if (BoxMesh)
	{
		BoxMesh->SetNotifyRigidBodyCollision(true);
		BoxMesh->OnComponentHit.AddDynamic(this, &APickupableItem::OnCompHit);

	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("BoxMesh is NULL in %s"), *GetName());
	}

	if (BoxComponent)
	{
		BoxComponent->OnComponentHit.AddDynamic(this, &APickupableItem::OnCompHit);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("WeaponMesh is NULL in %s"), *GetName());
	}
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


