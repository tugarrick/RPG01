// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Struct/ItemInfomation.h"
#include "TooltipWidget.generated.h"


class UTextBlock;
class UImage;
class UBorder;
class IInventoryInterface;
class UGridPanel;
class UStatBarWidget;
class UInventorySystemComponent;


UCLASS()
class RPG01_API UTooltipWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual bool Initialize() override;
	void UpdateWidget(int EquipmentSlotIndex);

public:
	UPROPERTY()
	TObjectPtr<UInventorySystemComponent> InventorySystem;

	int CurrentSlotType = 0;
	// 0 is Inventory Slot
	// 1 is EquipmentSlot

	UPROPERTY()
	FItemInfomation ItemInfo;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> ItemIcon;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemName;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemType;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemRarity;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemLevelRequest;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemInstruct;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBorder> TooltipBox;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBorder> HeaderBox;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UGridPanel> StatsGridPanel;

protected:
	UPROPERTY()
	TScriptInterface<IInventoryInterface> InventoryInterface;

};
