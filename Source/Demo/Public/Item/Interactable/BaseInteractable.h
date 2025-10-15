// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseInteractable.generated.h"

UENUM(BlueprintType)
enum class EItemCategory :uint8
{
	IC_NONE UMETA(DisplayName = "NONE"),
	IC_WEAPON UMETA(DisplayName = "Weapon"),
	IC_LEVER UMETA(DisplayName = "Lever"),
	IC_CONSUMBLE UMETA (DisplayName = "Consumble"),	
	IC_NOTES UMETA(DisplayName = "Notes")



};





UCLASS()
class DEMO_API ABaseInteractable : public AActor
{
	GENERATED_BODY()
	
public:	
	
	ABaseInteractable();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	class UWidgetComponent* WidgetComponent;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	class USceneComponent* SceneComponent;


	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly)
	EItemCategory ItemCategory;

	bool CheckWeapon(EItemCategory ItemCategory);


protected:
	UPROPERTY(EditAnywhere, BlueprintReadwrite, Category = "collision", meta = (AllowPrivateAccess = true))
	class UStaticMeshComponent* BoxMesh;


	UPROPERTY(VisibleAnywhere, BlueprintReadwrite, category = "collision", meta = (AllowPrivateAccess = true))
	class UBoxComponent* BoxComponent;


	UPROPERTY(VisibleAnywhere, BlueprintReadwrite, category = "collision", meta = (AllowPrivateAccess = true))
	class USphereComponent* SphereComponent;

	UFUNCTION()
	virtual	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult);


	UFUNCTION()
	virtual	void OnBoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);



	



	UFUNCTION()
	virtual	void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


	UFUNCTION()
	void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult);


	virtual void BeginPlay() override;

	virtual bool IsPickable()const { return false; }


	


public:	

	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable)
	virtual void Interact(AMainCharacter* Character)  PURE_VIRTUAL(ABaseInteractable::Interact, );

	FORCEINLINE  UWidgetComponent* GetWidgetComponent() { return WidgetComponent; }
	FORCEINLINE UStaticMeshComponent* GetMesh() { return BoxMesh; }

	FORCEINLINE USphereComponent* GetSphere() { return SphereComponent; }
	FORCEINLINE UBoxComponent* GetBox() { return BoxComponent; }

private:
	class AMainCharacter* CharacterRef;
	
};
