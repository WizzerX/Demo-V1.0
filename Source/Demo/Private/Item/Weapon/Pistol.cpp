// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Weapon/Pistol.h"
#include "Kismet/GameplayStatics.h"
#include "Niagara/Classes/NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "character/MainCharacter.h"
#include "Camera/CameraComponent.h"
APistol::APistol()
{
	


	//RecoilDuration = 0.5f;


	WeaponType = EItemType::Pistol;
	ItemCategory = EItemCategory::IC_WEAPON;
	EItemState::EIS_PickedUp;
}

void APistol::FireTheWeapon()
{

	UGameplayStatics::PlaySound2D(GetWorld(),ShootSound);
	//UNiagaraFunctionLibrary::SpawnSystemAttached(GunFlash,GetWeaponMesh(), FName("Muzzle"),
		//FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::SnapToTarget, true);

	UAnimInstance* AnimInstance = GetWeaponMesh()->GetAnimInstance();
	AnimInstance->Montage_Play(FireAnimation);


	if (!CharacterRef) return;

	if (CharacterRef)
	{
		UE_LOG(LogTemp, Warning, TEXT("Character %s"), CharacterRef);
		
		
		
		
		/*
		InitRot = BoxMesh->GetRelativeRotation();
		FinalRot = InitRot;
		FinalRot.Pitch += VerticleKick; // Move gun upward a bit
		*/
		
	}


}

void APistol::BeginPlay()
{
	Super::BeginPlay();

	


}

void APistol::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);




	if (bActiveRecoil)
	{
	
	}


}
