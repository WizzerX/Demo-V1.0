// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Weapon/Pistol.h"
#include "Kismet/GameplayStatics.h"
#include "Niagara/Classes/NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "character/MainCharacter.h"
#include "Camera/CameraComponent.h"
APistol::APistol()
{
	
	VerticleKick = -50.f;
	HorizontalKick = 2.3f;
	RecoverSpeed = .25f;
	RecoilSpeed = 100.f;
	CurrentRecoilTime = 0.f;

	RecoilDuration = 0.5f;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GunMesh"));
	WeaponMesh->SetupAttachment(GetRootComponent());
	
}

void APistol::FireTheWeapon()
{

	UGameplayStatics::PlaySound2D(GetWorld(),ShootSound);
	UNiagaraFunctionLibrary::SpawnSystemAttached(GunFlash,GetMesh(), FName("Muzzle"),
		FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::SnapToTarget, true);

	if (!CharacterRef) return;

	if (CharacterRef)
	{
		UE_LOG(LogTemp, Warning, TEXT("Character %s"), CharacterRef);
		
		bActiveRecoil = true;

		
		CurrentRecoilTime = 0.f;

		InitRot = BoxMesh->GetRelativeRotation();
		FinalRot = InitRot;
		FinalRot.Pitch += VerticleKick; // Move gun upward a bit
		
		
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
