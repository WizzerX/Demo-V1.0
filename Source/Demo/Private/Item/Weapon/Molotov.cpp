// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Weapon/Molotov.h"
#include <character/MainCharacter.h>
#include <Components/SphereComponent.h>
#include <Components/WidgetComponent.h>
#include <Components/BoxComponent.h>
#include "DrawDebugHelpers.h"
#include <Niagara/Classes/NiagaraSystem.h>
#include <Niagara/Public/NiagaraFunctionLibrary.h>
#include <Character/MainCharacterInstance.h>
#include <Item/Inventory/InventoryComponent.h>
#include <Item/Weapon/WeaponType.h>
#include <Kismet/GameplayStatics.h>
AMolotov::AMolotov()
{
	BoxMesh->SetVisibility(true);



    
}
void AMolotov::SetItemProperties(EItemState State)
{
    
    switch (State)
    {
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


    case EItemState::EIS_Equipped:
    {
        // Visibility
        BoxMesh->SetVisibility(true);
        WeaponMesh->SetVisibility(true);

        // Physics OFF
        BoxMesh->SetSimulatePhysics(false);
        WeaponMesh->SetSimulatePhysics(false);

        // Collision OFF (IMPORTANT)
        BoxMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

        SphereComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        BoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        break;

    }
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

    }
   
    
}

void AMolotov::OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!OtherActor || OtherActor == this || !OtherComp) return;


	if (ItemState == EItemState::EIS_Falling && OtherComp->GetCollisionObjectType() == ECC_WorldStatic)
	{
		UE_LOG(LogTemp, Warning, TEXT("Item Landed, switching to Pickup"));
		SetItemState(EItemState::EIS_Pickup);
		
		
			BlastMolotov();
		
		

	}




}

 void AMolotov::FireTheWeapon()
{

 CharacterAnimInstance = CharacterRef->GetMesh()->GetAnimInstance();
	CharacterAnimInstance->Montage_Play(AttackAnimation);
	
	
}
 void AMolotov::BlastMolotov()
 {
	 
	 FVector Loc = GetActorLocation();
	 DrawDebugSphere(GetWorld(), Loc, 300.f, 50, FColor::Red,false,5.f);
	 if (!FlameRadius)return;
	 UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), FlameRadius, Loc, FRotator::ZeroRotator);
	 UGameplayStatics::PlaySound2D(GetWorld(), ShootSound);
	 Destroy();
	
	 
 }
 void AMolotov::MolotovLogic()
 {
	 auto EquippedMolotov = CharacterRef->CurrentEquiped;
	 if (!EquippedMolotov) return;

	 UStaticMeshComponent* Mesh = EquippedMolotov->GetMesh();
	 if (!Mesh) return;

	 // Detach
	 Mesh->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);

	 // Enable physics
	 EquippedMolotov->SetItemState(EItemState::EIS_Falling);
	 Mesh->SetSimulatePhysics(true);
	 Mesh->WakeAllRigidBodies();

	 // Remove from inventory
	 int32 Index = CharacterRef->InventoryComponent
		 ->FindIndexById(EquippedMolotov->ItemData.IdCode);

	 CharacterRef->InventoryComponent->RemoveItemAt(Index);
	 CharacterRef->CurrentWeaponType = EItemType::None;

	 // Apply impulse TO THE SAME ACTOR
	 FVector ThrowImpulse =
		 CharacterRef->GetActorForwardVector() * 800.f +
		 FVector(0.f, 0.f, 750.f);

	 Mesh->AddImpulse(ThrowImpulse, NAME_None, true);
	 Mesh->AddAngularImpulseInDegrees(
		 FVector(
			 FMath::RandRange(-300.f, 300.f),
			 FMath::RandRange(-300.f, 300.f),
			 FMath::RandRange(-300.f, 300.f)),
		 NAME_None,
		 true
	 );
 }
