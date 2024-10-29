// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/InteractInterface.h"
#include "Struct/ItemInfomation.h"
#include "Interface/InventoryInterface.h"
#include "Interface/StatInterface.h"
#include "TreyCharacter.generated.h"

class USphereComponent;
class AInteractableItems;
class UInputMappingContext;
class UInputAction;
struct FItemInfomation;
class UStatComponent;
class UTreyCharacterData;
class UEnhancedInputData;
class UInventorySystemComponent;

UCLASS()
class RPG01_API ATreyCharacter : public ACharacter, public IInventoryInterface, public IStatInterface, public IInteractInterface
{
	GENERATED_BODY()

public:
	ATreyCharacter();
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void SphereComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void SphereComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void SetupInputMappingContext();
	void Pickup();
	void ToggleInventory();

	void PickupItem(FItemInfomation& ItemInfo);
	void AttachItem(int EquipmentIndex, FItemInfomation& ItemInfo);
	void DetachItem(int EquipmentIndex);

	//Interact Interface
	virtual void I_Interact(AActor* InActor) override;

	//Inventory Interface
	virtual UInventorySystemComponent* GetInventorySystem() override;
	virtual void AddAttachedItem(int EquipmentIndex, FItemInfomation& ItemInfo) override;
	virtual void RemoveAttachedItem(int EquipmentIndex, FItemInfomation& ItemInfo, bool bChangeCurrentStats) override;

	//Stat Interface
	virtual float GetCurrentStat(const EStat& Stat) override;
	virtual float GetMaxStat(const EStat& Stat) override;
	virtual float GetBaseStat(const EStat& Stat) override;
	
protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY()
	TObjectPtr<APlayerController> PlayerController;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<USkeletalMeshComponent> MeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<USkeletalMeshComponent> ChestComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<USkeletalMeshComponent> HandsComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<USkeletalMeshComponent> LegsComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<USkeletalMeshComponent> FeetComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> SphereComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UStatComponent> StatComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UInventorySystemComponent> InventorySystem;

	UPROPERTY()
	TArray<TObjectPtr<AInteractableItems>> InteractableActors;

	UPROPERTY()
	TMap<int, TObjectPtr<AActor>> AttachedActors;


	UPROPERTY(BlueprintReadWrite)
	bool bCanMove = true;

	UPROPERTY(BlueprintReadWrite)
	int InventorySize = 36;

	UPROPERTY(EditDefaultsOnly, Category = "Data Asset")
	TObjectPtr<UTreyCharacterData> TreyCharacterData;

	UPROPERTY(EditDefaultsOnly, Category = "Data Asset")
	TObjectPtr<UEnhancedInputData> EnhancedInputData;

	
};
