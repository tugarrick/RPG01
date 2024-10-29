// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Struct/ItemInfomation.h"
#include "InventorySystemComponent.generated.h"

class UInventorySystemData;
class UInventoryWidget;
class UInventorySlotWidget;
class UUserWidget;
class APreviewTreyCharacter;
class UTooltipWidget;
class UItemOptionWidget;
class UStatBarWidget;
class URarityData;
class UInterfaceWidget;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RPG01_API UInventorySystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInventorySystemComponent();
	void Init(APlayerController* PlayerController);

	void OpenInventory();
	void CloseInventory();

	void AddItem(FItemInfomation& ItemInfo);
	void RemoveItem(int InventoryIndex);

	UFUNCTION(BlueprintCallable)
	void DropItem(int InventoryIndex, FItemInfomation& ItemInfo);

	int GetEmptySlotIndex();

protected:
	virtual void BeginPlay() override;

public:	

	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UPROPERTY(EditDefaultsOnly, Category = "Data Asset");
	TObjectPtr<UInventorySystemData> InventorySystemData;

	UPROPERTY(EditDefaultsOnly, Category = "Data Asset");
	TObjectPtr<URarityData> RarityData;

	UPROPERTY()
	TObjectPtr<APlayerController> PlayerController;

	UPROPERTY()
	TObjectPtr<UInterfaceWidget> InterfaceWidget;

	UPROPERTY()
	TObjectPtr<UInventoryWidget> InventoryWidget;

	UPROPERTY()
	TObjectPtr<UInventorySlotWidget> InventorySlotWidget;

	UPROPERTY()
	TObjectPtr<UUserWidget> EquipmentPreviewWidget;

	UPROPERTY()
	TArray<FItemInfomation> Inventory;

	UPROPERTY()
	TMap<int, FItemInfomation> AttachedEquipment;

	UPROPERTY()
	TObjectPtr<APreviewTreyCharacter> PreviewTreyCharacter;

	//UPROPERTY()
	//TObjectPtr<ATreyCharacter> OwningCharacter;
};
