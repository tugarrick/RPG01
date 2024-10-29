// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Struct/ItemInfomation.h"
#include "EquipmentSlotWidget.generated.h"

class UButton;
class UImage;
class IInventoryInterface;
class UInventorySystemComponent;

UCLASS()
class RPG01_API UEquipmentSlotWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual bool Initialize() override;

	void UpdateWidget();

	UFUNCTION()
	void OnClickedItemIcon();
public:

	UPROPERTY()
	TObjectPtr<UInventorySystemComponent> InventorySystem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int EquipmentSlotIndex = 0;

	UPROPERTY()
	FItemInfomation ItemInfo;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ItemButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> ItemIcon;

protected:
	UPROPERTY()
	TScriptInterface<IInventoryInterface> InventoryInterface;
};
