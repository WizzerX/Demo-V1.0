// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseInteractable.h"
#include "Item/Weapon/WeaponType.h"
#include "PickupableItem.generated.h"


USTRUCT(BlueprintType)
struct FInventoryItemData
{
	GENERATED_BODY()

public:
	

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Item")
	FName ItemName;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Item")
	FName Description;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Item")
	int	Quantity;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Item")
	FGuid IdCode;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Item")
	class UTexture2D* Icon = nullptr;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Item")
	bool stackable = false;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FName SocketName = "";

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Item")
	TSubclassOf<APickupableItem>ItemActorClass;

	FInventoryItemData() :
		ItemName(""),
		Quantity(0),
		Icon(nullptr)
	{}



};



UENUM(BlueprintType)
enum class EItemState :uint8
{
	EIS_Pickup UMETA(DisplayName = "Pickup"),
	EIS_EquipInterping UMETA(DisplayName = "EquipInterping"),
	EIS_PickedUp UMETA(DisplayName = "PickedUp"),
	EIS_Equipped UMETA(DisplayName = "Equipped"),
	EIS_Falling UMETA(DisplayName = "Falling"),

	EIS_MAX UMETA(DisplayName = "DefaultMAX")
};





UCLASS()
class DEMO_API APickupableItem : public ABaseInteractable
{
	GENERATED_BODY()
	
public:

	APickupableItem();
	void SetItemState(EItemState state);
	virtual bool IsPickable()const { return true; }

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FName SlotName;





protected:
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	EItemState ItemState;


	



virtual	void SetItemProperties(EItemState State);

	virtual void BeginPlay() override;
	
	class AMainCharacter* CharacterRef;

private:


	virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;


	void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);




	

	
public:
	virtual void Interact(AMainCharacter* Character) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FInventoryItemData ItemData;
	UFUNCTION()
		virtual void OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			FVector NormalImpulse, const FHitResult& Hit);


	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "ItemType")
		EItemType ItemType;


};
