// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.generated.h"


USTRUCT(BlueprintType)
struct FItemData
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FText ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 Count;

	


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
class DEMO_API AInteractable : public AActor
{
	GENERATED_BODY()
	
public:	

	AInteractable();

	bool bInteractable = false;

	
protected:

	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere, BlueprintReadwrite, category = "collision", meta = (AllowPrivateAccess = true))
		class UBoxComponent* BoxComponent;

		UPROPERTY(VisibleAnywhere, BlueprintReadwrite, category = "collision", meta = (AllowPrivateAccess = true))
		class USphereComponent* SphereComponent;


	UPROPERTY(EditAnywhere, BlueprintReadwrite, Category = "collision", meta = (AllowPrivateAccess = true))
		class UStaticMeshComponent* BoxMesh;

		UFUNCTION()
	virtual	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp,int32 OtherBodyIndex, bool bFromSweep, 
			const FHitResult& SweepResult);


		UFUNCTION()
	virtual	void OnBoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


		UFUNCTION()
		void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
			const FHitResult& SweepResult);




		UFUNCTION()
		void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

		virtual void Tick(float deltatime) override;


protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
	FItemData ItemData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	class UWidgetComponent* WidgetComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	EItemState ItemState;

public:	

	FORCEINLINE  UWidgetComponent* GetWidgetComponent() { return WidgetComponent; }
	FORCEINLINE UStaticMeshComponent* GetMesh() { return BoxMesh; }
	FORCEINLINE USceneComponent* GetRoot() { return SceneRoot; }
	FORCEINLINE USphereComponent* GetSphere() { return SphereComponent; }
	FORCEINLINE UBoxComponent* GetBox() { return BoxComponent; }
	FORCEINLINE EItemState GetItemState()const { return ItemState; }
	void SetItemState(EItemState State);
public :
	class AMainCharacter* CharacterRef;

	UFUNCTION()
	void OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		FVector NormalImpulse, const FHitResult& Hit);

	void CheckIfLanded();

private:
	void SetItemProperties(EItemState State);
	UPROPERTY(EditAnywhere);
	USceneComponent* SceneRoot;
};
