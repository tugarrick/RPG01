// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Struct/ItemInfomation.h"
#include "InventoryWidget.generated.h"

class UGridPanel;
class IInventoryInterface;
class IStatInterface;
class UBorder;
class UTextBlock;
class UImage;
class UInventorySystemComponent;
class APreviewTreyCharacter;

UCLASS()
class RPG01_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual bool Initialize() override;

	void BuildInventory();

	void ShowStatsDelta(int EquipmentSlotIndex, FItemInfomation& ItemInfo);

	void HideStatsDelta();

	void RefreshEquipmentSlots();
	void RefreshInventorySlots();

	void RefreshStatStatus();
	
public:

	UPROPERTY()
	TObjectPtr<UInventorySystemComponent> InventorySystem;

	UPROPERTY()
	TObjectPtr<APlayerController> PlayerController;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UGridPanel> InventoryGrid;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBorder> InventoryBox;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBorder> EquipmentBox;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> HealthValue;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> HealthDelta;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> HealthUnderline;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> StaminaValue;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> StaminaDelta;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> StaminaUnderline;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ManaValue;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ManaDelta;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> ManaUnderline;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ArmorValue;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ArmorDelta;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> ArmorUnderline;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> PhysicalDamageValue;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> PhysicalDamageDelta;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> PhysicalDamageUnderline;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> MagicalDamageValue;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> MagicalDamageDelta;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> MagicalDamageUnderline;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> MovementSpeedValue;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> MovementSpeedDelta;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> MovementSpeedUnderline;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> AttackSpeedValue;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> AttackSpeedDelta;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> AttackSpeedUnderline;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> CooldownValue;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> CooldownDelta;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> CooldownUnderline;

protected:
	UPROPERTY()
	TScriptInterface<IInventoryInterface> InventoryInterface;

	UPROPERTY()
	TScriptInterface<IStatInterface> StatInterface;

};
