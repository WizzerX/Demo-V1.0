// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Weapon/Rifile.h"
#include "Animation/AnimInstance.h"
#include <Kismet/GameplayStatics.h>
#include <character/MainCharacter.h>
#include <Niagara/Classes/NiagaraSystem.h>
#include <Niagara/Public/NiagaraFunctionLibrary.h>
ARifile::ARifile()
{

	FireRate = .2f;


}

void ARifile::FireTheWeapon()
{
	


	UE_LOG(LogTemp, Warning, TEXT("Fireing The Rifile"));

	//StartFire(); // fire instantly once

	GetWorld()->GetTimerManager().SetTimer(Timer,this,&ARifile::StartFire,FireRate,true,0.f);
	

}




	


void ARifile::StartFire()
{
	

	UE_LOG(LogTemp, Warning, TEXT("StartFireing2"));

	UAnimInstance* AnimInstance = GetWeaponMesh()->GetAnimInstance();
	if (!AnimInstance)return;
	if (!GunFlash)return;
	AnimInstance->Montage_Play(FireAnimation);

	UGameplayStatics::PlaySound2D(GetWorld(), ShootSound);
	/*
	UNiagaraFunctionLibrary::SpawnSystemAttached(
		GunFlash,
		GetWeaponMesh(),
		MuzzleName,
		FVector::ZeroVector,
		FRotator::ZeroRotator,
		EAttachLocation::SnapToTarget,
		true
	);
	*/

	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, GetWeaponMesh(), MuzzleName, FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::SnapToTarget);
	CharacterRef->PlayCameraShake(WeaponFireShake);

}

void ARifile::StopFire()
{
	GetWorld()->GetTimerManager().ClearTimer(Timer);
}
