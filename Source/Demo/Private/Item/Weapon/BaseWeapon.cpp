// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Weapon/BaseWeapon.h"

ABaseWeapon::ABaseWeapon()
{
	
	SceneComponent->SetRelativeLocation(FVector(0.0, 0.0f,280.f));

	ItemCategory = EItemCategory::IC_WEAPON;
}
