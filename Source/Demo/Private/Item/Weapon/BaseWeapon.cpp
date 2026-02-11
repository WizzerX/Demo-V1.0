// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Weapon/BaseWeapon.h"
#include "Character/MainCharacter.h"
#include "GameFramework/Character.h"
#include "Animation/AnimInstance.h"
#include <Kismet/GameplayStatics.h>
#include <Niagara/Classes/NiagaraSystem.h>
ABaseWeapon::ABaseWeapon()
{
	
	//SceneComponent->SetRelativeLocation(FVector(0.0, 0.0f,280.f));

	//WeaponMesh = CreateDefaultSubobject  <USkeletalMeshComponent > (TEXT("WeaponMesh"));
	//WeaponMesh->AttachTo(GetRootComponent());
	
	//GunFlash = CreateDefaultSubobject<UNiagaraSystem>(TEXT("NiagaraSystem"));
	

	

ItemType = EItemType::None;
	
}

void ABaseWeapon::PlayAttackMontage()
{
	if (!AttackAnimation)return;
	//if (!AttackSound)return;
	 UAnimInstance* Character=CharacterRef->GetMesh()->GetAnimInstance();
	 if (!Character)return;

	 Character->Montage_Play(AttackAnimation);
	 //UGameplayStatics::PlaySound2D(GetWorld(),AttackSound);
	 UE_LOG(LogTemp, Warning, TEXT("Play the Montage"));
}
