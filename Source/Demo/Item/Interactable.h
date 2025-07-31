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


	UPROPERTY(VisibleAnywhere, BlueprintReadwrite, Category = "collision", meta = (AllowPrivateAccess = true))
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


		UPROPERTY(VisibleAnywhere)
		USceneComponent* SceneRoot;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
	FItemData ItemData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	class UWidgetComponent* WidgetComponent;

	
public:	

	FORCEINLINE  UWidgetComponent* GetWidgetComponent() { return WidgetComponent; }


public :
	class AMainCharacter* CharacterRef;


	
	
};
