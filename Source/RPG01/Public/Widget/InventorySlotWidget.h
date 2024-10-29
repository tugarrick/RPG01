// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Struct/ItemInfomation.h"
#include "InventorySlotWidget.generated.h"

class UTextBlock;
class UButton;
class UImage;
class IInventoryInterface;
class UItemOptionWidget;
class UInventorySystemComponent;

UCLASS()
class RPG01_API UInventorySlotWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual bool Initialize() override;
	
	void UpdateWidget();


protected:

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	UFUNCTION()
	void OnClickedItemIcon();

	UFUNCTION()
	void OnHoveredItemIcon();

	UFUNCTION()
	void OnUnhoveredItemIcon();
public:

	UPROPERTY()
	TObjectPtr<UInventorySystemComponent> InventorySystem;

	UPROPERTY()
	int InventoryIndex = 0;

	UPROPERTY()
	int EquipmentSlotIndex = 0;

	UPROPERTY()
	FItemInfomation ItemInfo;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ItemButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> ItemIcon;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemQuantity;

	UPROPERTY()
	TObjectPtr<UItemOptionWidget> ItemOptionWidget;

protected:
	UPROPERTY()
	TScriptInterface<IInventoryInterface> InventoryInterface;
	
};
