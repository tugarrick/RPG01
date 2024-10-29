// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TreyCharacterData.generated.h"

class UInterfaceWidget;
class UInventoryWidget;
class UInventorySlotWidget;
class UTooltipWidget;
class UNotifyBoxWidget;
class UNotifyWidget;
class UItemOptionWidget;
class UStatBarWidget;
class APreviewTreyCharacter;
class AInteractableItems;

UCLASS()
class RPG01_API UTreyCharacterData : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, Category = "Widget")
	TSubclassOf<UInterfaceWidget> InterfaceWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widget")
	TSubclassOf<UInventoryWidget> InventoryWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widget")
	TSubclassOf<UInventorySlotWidget> InventorySlotWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widget")
	TSubclassOf<UUserWidget> EquipmentPreviewWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widget")
	TSubclassOf<UTooltipWidget> TooltipWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widget")
	TSubclassOf<UNotifyBoxWidget> NotifyBoxWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widget")
	TSubclassOf<UNotifyWidget> NotifyWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widget")
	TSubclassOf<UItemOptionWidget> ItemOptionWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widget")
	TSubclassOf<UStatBarWidget> StatBarWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Background")
	TArray<TObjectPtr<UTexture>> ItemTypeBGIcons;

	UPROPERTY(EditDefaultsOnly, Category = "Background")
	TArray<TObjectPtr<UTexture>> StatTypeBGIcons;

	UPROPERTY(EditDefaultsOnly, Category = "Background")
	TObjectPtr<UTexture> IncreaseImage;

	UPROPERTY(EditDefaultsOnly, Category = "Background")
	TObjectPtr<UTexture> DecreaseImage;

	UPROPERTY(EditDefaultsOnly, Category = "Preview")
	TSubclassOf<APreviewTreyCharacter> PreviewTreyCharacterClass;

	UPROPERTY(EditDefaultsOnly, Category = "Item")
	TSubclassOf<AInteractableItems> InteractableItemsClass;
};
